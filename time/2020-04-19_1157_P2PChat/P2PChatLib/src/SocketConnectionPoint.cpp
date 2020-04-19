#include "SocketConnectionPoint.h"
#include "SocketWrapperLib/SocketWrapperShared.h"
#include "ChatException.hpp"

struct SocketConnectionPoint::impl {
    TCPSocketPtr clientSocket;
};

const int GOOD_SEGMENT_SIZE = 1300;

SocketConnectionPoint::SocketConnectionPoint()
{
    m_pimpl = std::make_unique<impl>();
}

void SocketConnectionPoint::accept(std::string connectInfo)
{
    TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(INET);
    SocketAddress receivingAddress(INADDR_ANY, 48000);
    if (listenSocket->Bind(receivingAddress) != NO_ERROR)
    {
        m_status = CpStatus::ConnectionError;
        return;
    }
    listenSocket->Listen();
    SocketAddress newClientAddress;
    m_pimpl->clientSocket = listenSocket->Accept(newClientAddress);
    m_pimpl->clientSocket->SetNonBlockingMode(true);
}

void SocketConnectionPoint::connect(std::string connectInfo)
{
    SocketAddressPtr newClientAddress = SocketAddressFactory::CreateIPv4FromString(connectInfo);
    if(!newClientAddress)
    {
        throw ChatException("Error CreateIPv4FromString in SocketConnectionPoint::connect");
    }
    m_pimpl->clientSocket = SocketUtil::CreateTCPSocket(INET);
    m_pimpl->clientSocket->Connect(*newClientAddress);
}


void SocketConnectionPoint::send(std::string msg)
{
    msg.resize(GOOD_SEGMENT_SIZE-1);
    msg += '\0';
    const char * segment = msg.c_str();
    int bytesSent = m_pimpl->clientSocket->Send(segment, GOOD_SEGMENT_SIZE);
}

std::string SocketConnectionPoint::receive()
{
    char segment[GOOD_SEGMENT_SIZE] = {};
    int bytesReceived = m_pimpl->clientSocket->Receive(segment, GOOD_SEGMENT_SIZE);
    return segment;
}

void SocketConnectionPoint::disconnect()
{
    m_pimpl->clientSocket.reset();
}

CpStatus SocketConnectionPoint::getStatus()
{
    return m_status;
}
