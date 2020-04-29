#include "ServerCore.h"

#include <map>

#include "SocketWrapperLib\SocketWrapperShared.h"
#include "ChatITF/ChatException.hpp"

const int GOOD_SEGMENT_SIZE = 300;

void serverErrorCallBack(ILoggerPtr logger, std::string error)
{
    logger->LogTrace(error);
}

struct ServerCore::impl
{
    IUserInterfacePtr ui;
    ILoggerPtr logger;
    bool isServerRunning;
    TCPSocketPtr listenSocket;
    std::vector<TCPSocketPtr> readBlockSockets;
    std::map<TCPSocketPtr, SocketAddress> socketToAddressTable;

    void onClientConnect(TCPSocketPtr newSocket, SocketAddress newClientAddress)
    {
        logger->LogInfo("Connected client: " + newClientAddress.ToString());
        readBlockSockets.push_back(newSocket);
        socketToAddressTable[newSocket] = newClientAddress;

        std::string replyForAll = "Connected client: " + newClientAddress.ToString()
        + ". Count clients is " + std::to_string(socketToAddressTable.size()) + ".\0";

        for (auto s : readBlockSockets)
        {
            if (s != listenSocket && s != newSocket)
            {
                s->Send(static_cast<const void*>(replyForAll.c_str()), replyForAll.length());
            }
        }

        std::string replyForCurrentUser = "Count clients is " + std::to_string(socketToAddressTable.size()) + ".\0";

        newSocket->Send(static_cast<const void*>(replyForCurrentUser.c_str()), replyForCurrentUser.length());
    }

    void onClientDisconnect(TCPSocketPtr socket)
    {
        logger->LogInfo("onClientDisconnect");
        auto& ss = readBlockSockets;

        std::string reply = "Disconnected client: " + socketToAddressTable.at(socket).ToString()
            + ". Count clients is " + std::to_string(socketToAddressTable.size() - 1) + ".\0";

        ss.erase(std::remove(ss.begin(), ss.end(), socket), ss.end());
        socketToAddressTable.erase(socket);

        for (auto s : readBlockSockets)
        {
            if (s != listenSocket)
            {
                s->Send(static_cast<const void*>(reply.c_str()), reply.length());
            }
        }
    }

    void processDataFromClient(TCPSocketPtr socket, char * segment, int32_t dataReceived)
    {
        std::string recvMsg = segment;
        size_t msgLenght = recvMsg.length();
        logger->LogInfo("Received msg from client. TransportSize=" + std::to_string(dataReceived)
            + " bytes; MsgLenght=" + std::to_string(msgLenght));
        logger->LogInfo("Msg: " + recvMsg);

        if(msgLenght == 0)
            return;

        std::string reply = socketToAddressTable.at(socket).ToString() + ": " + recvMsg + '\0';

        for (auto s : readBlockSockets)
        {
            if(s != listenSocket && s != socket)
            {
                s->Send(static_cast<const void*>(reply.c_str()), reply.length());
            }
        }
    }

};

ServerCore::ServerCore(IUserInterfacePtr ui, ILoggerPtr logger)
{
    SocketUtil::StaticInit();
    std::function<void(std::string)> bindedCallBack = std::bind(serverErrorCallBack, logger, std::placeholders::_1);
    SocketUtil::SetErrorCallBack(bindedCallBack);
    m_pimpl = std::make_unique<impl>();
    m_pimpl->ui = ui; // TODO read port
    m_pimpl->logger = logger;
    m_pimpl->isServerRunning = false;
    m_pimpl->logger->LogInfo("ChatServer v0.1 started");
}

ServerCore::~ServerCore()
{
    SocketUtil::CleanUp();
}

void ServerCore::start()
{
    m_pimpl->isServerRunning = true; // TODO
    auto ci = m_pimpl->ui->getConnectionInfo();

    m_pimpl->listenSocket = SocketUtil::CreateTCPSocket(INET);
    auto receivingAddress = SocketAddressFactory::CreateIPv4FromString(ci.ipV4_ip_port);
    if(m_pimpl->listenSocket->Bind(*receivingAddress) != NO_ERROR)
    {
        throw ChatException("Listen Socket Bind Errors");
    }
    m_pimpl->logger->LogInfo("Listen raw=" + ci.ipV4_ip_port + "; converted=" + receivingAddress->ToString());
    
    if (m_pimpl->listenSocket->Listen() != NO_ERROR)
    {
        throw ChatException("listenSocket->Listen() != NO_ERROR");
    }

    m_pimpl->readBlockSockets.push_back(m_pimpl->listenSocket);

    while (m_pimpl->isServerRunning)
    {
        std::vector<TCPSocketPtr> readableSockets;
        auto isPacketReceived = SocketUtil::Select(&m_pimpl->readBlockSockets, &readableSockets,
            nullptr, nullptr, nullptr, nullptr);

        if(isPacketReceived)
        {
            for(auto socket : readableSockets)
            {
                if(socket == m_pimpl->listenSocket)
                {
                    SocketAddress newClientAddress;
                    auto newSocket = m_pimpl->listenSocket->Accept(newClientAddress);
                    m_pimpl->onClientConnect(newSocket, newClientAddress);
                }
                else
                {
                    char segment[GOOD_SEGMENT_SIZE];
                    auto dataReceived = socket->Receive(segment, GOOD_SEGMENT_SIZE);
                    if(dataReceived > 0)
                    {
                        m_pimpl->processDataFromClient(socket, segment, dataReceived);
                    }
                    else if(dataReceived == -WSAECONNRESET)
                    {
                        m_pimpl->onClientDisconnect(socket);
                    }
                }
            }
        }

    }
}
