#pragma once

#include "StdPlus/StdPlus.h"
#include "OopSocket/OopSocket.h"

class ChatServer
{
public:
    ChatServer()
    {
        SocketUtil::StaticInit();
    }

    ~ChatServer()
    {
        SocketUtil::CleanUp();
    }

    void setCmdArgs(int argc, char** argv)
    {
        stdplus::CmdParser cmd;
        cmd.parseData(argc, argv);
        m_bindIp = cmd.getValue<std::string>("bindIp", "127.0.0.1");
        m_bindPort = cmd.getValue<uint16_t>("bindPort", 12345);
        m_backlog = cmd.getValue<int>("backlog", 10);
    }

    void start()
    {
        AMSG(std::string("started listen ") + m_bindIp 
            + ":" + stdplus::to_string(m_bindPort) 
            + "(" + stdplus::to_string(m_backlog) +")");

        m_listenSocket = SocketUtil::CreateTCPSocket(INET);
        m_listenSocket->Bind(SocketAddress(m_bindIp, m_bindPort));
        m_listenSocket->Listen(m_backlog);

        SocketAddress addressNewClient;
        auto clientSocket = m_listenSocket->Accept(addressNewClient);
        AVAR(addressNewClient);


        std::string recvMsg;
        Transfer::recv(clientSocket, &recvMsg);
        AVAR(recvMsg);


        std::vector<std::string> recieveMessages;
        Transfer::recv(clientSocket, &recieveMessages);
        AVAR(recieveMessages);
    }

private:
    std::string  m_bindIp;
    uint16_t     m_bindPort;
    int          m_backlog;
    TCPSocketPtr m_listenSocket;

};
