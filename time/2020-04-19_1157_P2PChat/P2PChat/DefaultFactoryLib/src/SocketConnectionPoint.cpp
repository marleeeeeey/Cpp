#include "SocketConnectionPoint.h"
#include "SocketWrapperLib/SocketWrapperShared.h"
#include "ChatITF\ChatException.hpp"
#include <mutex>
#include <functional>

const int GOOD_SEGMENT_SIZE = 300;

struct SocketConnectionPoint::impl {
    TCPSocketPtr clientSocket;
    std::mutex socketMutex;
    CpStatus status;
    ILoggerPtr logger;
};

void errorCallBack(ILoggerPtr logger, std::string error)
{
    logger->LogTrace(error);
}

SocketConnectionPoint::SocketConnectionPoint(ILoggerPtr logger)
{
    SocketUtil::StaticInit();
    std::function<void(std::string)> bindedCallBack = std::bind(errorCallBack, logger, std::placeholders::_1);
    SocketUtil::SetErrorCallBack(bindedCallBack);
    m_pimpl = std::make_unique<impl>();
    m_pimpl->logger = logger;
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
    m_pimpl->logger->LogInfo("Binding " + receivingAddress->ToString());
    if (listenSocket->Bind(*receivingAddress) != NO_ERROR)
    {
        m_pimpl->status = CpStatus::ConnectionError;
        m_pimpl->logger->LogError("Error: listenSocket->Bind()");
        return;
    }
    m_pimpl->logger->LogTrace("Bind OK: " + receivingAddress->ToString());


    if(listenSocket->Listen() != NO_ERROR)
    {
        m_pimpl->status = CpStatus::ConnectionError;
        m_pimpl->logger->LogError("Error: listenSocket->Listen()");
        return;
    }
    m_pimpl->logger->LogTrace("Listen OK");
    m_pimpl->logger->LogInfo("Waiting clients");


    SocketAddress newClientAddress;
    m_pimpl->clientSocket = listenSocket->Accept(newClientAddress);
    m_pimpl->logger->LogInfo(std::string("Connected client ") + newClientAddress.ToString());
    m_pimpl->clientSocket->SetNonBlockingMode(true); // TODO
    m_pimpl->status = CpStatus::Connected;
}

void SocketConnectionPoint::connect(ConnectionInfo connectInfo)
{
    m_pimpl->logger->LogTrace("SocketConnectionPoint::connect");
    SocketAddressPtr clientAddress = SocketAddressFactory::CreateIPv4FromString(connectInfo.ipV4_ip_port);
    if(!clientAddress)
    {
        throw ChatException("CreateIPv4FromString from string='" + connectInfo.ipV4_ip_port + "' failed with error");
    }
    m_pimpl->clientSocket = SocketUtil::CreateTCPSocket(INET);
    m_pimpl->logger->LogInfo("Connection to server: " + clientAddress->ToString());
    auto connectionResult = m_pimpl->clientSocket->Connect(*clientAddress);
    if(connectionResult != NO_ERROR)
    {
        throw ChatException("Socket connection error");
    }
    m_pimpl->clientSocket->SetNonBlockingMode(true); // TODO
    m_pimpl->status = CpStatus::Connected;
    m_pimpl->logger->LogInfo("Connection successful");
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
        m_pimpl->status = CpStatus::ConnectionError;
        m_pimpl->logger->LogError("Connection error during SocketConnectionPoint::send. Error=" + std::to_string(-bytesSent));
    }
}

std::string SocketConnectionPoint::receive()
{
    std::lock_guard<std::mutex> lg(m_pimpl->socketMutex);
    char segment[GOOD_SEGMENT_SIZE] = {};

    int bytesReceived = m_pimpl->clientSocket->Receive(segment, 0);
    if (bytesReceived < 0 && -bytesReceived != WSAEWOULDBLOCK)
    {
        m_pimpl->status = CpStatus::ConnectionError;
        m_pimpl->logger->LogError("Connection error during SocketConnectionPoint::receive(0). Error=" + std::to_string(-bytesReceived));
    }
    else
    {
        bytesReceived = m_pimpl->clientSocket->Receive(segment, GOOD_SEGMENT_SIZE);
    }

    return segment;
}

void SocketConnectionPoint::disconnect()
{
    m_pimpl->status = CpStatus::Disconnected;
    m_pimpl->clientSocket.reset();
}

CpStatus SocketConnectionPoint::getStatus()
{
    return m_pimpl->status;
}
