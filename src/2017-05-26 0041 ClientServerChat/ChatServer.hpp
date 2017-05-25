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

        while (true)
        {
            SocketAddress addressNewClient;
            std::shared_ptr<TCPSocket> clientSocket
                = m_listenSocket->Accept(addressNewClient);
            AVAR(addressNewClient);

        }

    }

private:
    std::string  m_bindIp;
    uint16_t     m_bindPort;
    int          m_backlog;
    TCPSocketPtr m_listenSocket;

};
