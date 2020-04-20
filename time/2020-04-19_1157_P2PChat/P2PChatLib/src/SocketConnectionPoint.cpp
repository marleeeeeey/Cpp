#include "SocketConnectionPoint.h"
#include "SocketWrapperLib/SocketWrapperShared.h"
#include "ChatException.hpp"
#include <mutex>

const int GOOD_SEGMENT_SIZE = 300;

struct SocketConnectionPoint::impl {
    TCPSocketPtr clientSocket;
    std::mutex socketMutex;
};

SocketConnectionPoint::SocketConnectionPoint(ILoggerPtr logger)
{
    SocketUtil::StaticInit();
    m_pimpl = std::make_unique<impl>();
    m_logger = logger;
}

SocketConnectionPoint::~SocketConnectionPoint()
{
    disconnect();
    SocketUtil::CleanUp();
}

void SocketConnectionPoint::accept(ConnectionInfo connectInfo)
{
    TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(INET);
    auto receivingAddress = SocketAddressFactory::CreateIPv4FromString(connectInfo.ipV4_ip_port);
    m_logger->LogInfo("Binding " + receivingAddress->ToString());
    if (listenSocket->Bind(*receivingAddress) != NO_ERROR)
    {
        m_status = CpStatus::ConnectionError;
        m_logger->LogError("Error: listenSocket->Bind()");
        return;
    }
    m_logger->LogTrace("Bind OK: " + receivingAddress->ToString());


    if(listenSocket->Listen() != NO_ERROR)
    {
        m_status = CpStatus::ConnectionError;
        m_logger->LogError("Error: listenSocket->Listen()");
        return;
    }
    m_logger->LogTrace("Listen OK");
    m_logger->LogInfo("Waiting clients");


    SocketAddress newClientAddress;
    m_pimpl->clientSocket = listenSocket->Accept(newClientAddress);
    m_logger->LogInfo(std::string("Connected client ") + newClientAddress.ToString());
    m_pimpl->clientSocket->SetNonBlockingMode(true); // TODO
    m_status = CpStatus::Connected;
}

void SocketConnectionPoint::connect(ConnectionInfo connectInfo)
{
    m_logger->LogTrace("SocketConnectionPoint::connect");
    SocketAddressPtr clientAddress = SocketAddressFactory::CreateIPv4FromString(connectInfo.ipV4_ip_port);
    if(!clientAddress)
    {
        throw ChatException("Error CreateIPv4FromString in SocketConnectionPoint::connect");
    }
    m_pimpl->clientSocket = SocketUtil::CreateTCPSocket(INET);
    m_logger->LogInfo("Connection to server: " + clientAddress->ToString());
    m_pimpl->clientSocket->Connect(*clientAddress);
    m_pimpl->clientSocket->SetNonBlockingMode(true); // TODO
    m_status = CpStatus::Connected;
    m_logger->LogInfo("Connection successful");
}


void SocketConnectionPoint::send(std::string msg)
{
    std::lock_guard<std::mutex> lg(m_pimpl->socketMutex);
    msg.resize(GOOD_SEGMENT_SIZE-1);
    msg += '\0';
    const char * segment = msg.c_str();
    int bytesSent = m_pimpl->clientSocket->Send(segment, GOOD_SEGMENT_SIZE);
    if(bytesSent < 0)
    {
        m_status = CpStatus::ConnectionError;
        m_logger->LogError("Connection error during SocketConnectionPoint::send. Error=" + std::to_string(-bytesSent));
    }
}

std::string SocketConnectionPoint::receive()
{
    std::lock_guard<std::mutex> lg(m_pimpl->socketMutex);
    char segment[GOOD_SEGMENT_SIZE] = {};

    int bytesReceived = m_pimpl->clientSocket->Receive(segment, 0);
    if (bytesReceived < 0 && -bytesReceived != WSAEWOULDBLOCK)
    {
        m_status = CpStatus::ConnectionError;
        m_logger->LogError("Connection error during SocketConnectionPoint::receive(0). Error=" + std::to_string(-bytesReceived));
    }
    else
    {
        int bytesReceived = m_pimpl->clientSocket->Receive(segment, GOOD_SEGMENT_SIZE);
    }

    return segment;
}

void SocketConnectionPoint::disconnect()
{
    m_status = CpStatus::Disconnected;
    m_pimpl->clientSocket.reset();
}

CpStatus SocketConnectionPoint::getStatus()
{
    return m_status;
}
