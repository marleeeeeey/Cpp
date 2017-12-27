#pragma once

#include "OopSocket/OopSocket.h"

class ChatClient
{
public:
    ChatClient()
    {
        SocketUtil::StaticInit();
    }

    ~ChatClient()
    {
        SocketUtil::CleanUp();
    }

    void setCmdArgs(int argc, char** argv)
    {
        stdplus::CmdParser cmd;
        cmd.parseData(argc, argv);
        m_serverIp = cmd.getValue<std::string>("ip", "127.0.0.1");
        m_serverPort = cmd.getValue<uint16_t>("port", 12345);
    }

    void start()
    {
        AMSG(std::string("started listen ") + m_serverIp
            + ":" + stdplus::to_string(m_serverPort));

        m_socket = SocketUtil::CreateTCPSocket(INET);
        m_socket->Connect(SocketAddress(m_serverIp, m_serverPort));

        std::string sendMsg = "Hahahah";
        Transfer::send(m_socket, sendMsg);
        AVAR(sendMsg);


        std::vector<std::string> sendMassages
        {
            "qwer", "adfasdfasdfasdf", "oiuo",
            "hjkghkghjk", "dfghdfghdfgh", "cbcv",
        };

        AVAR(sendMassages);
        Transfer::send(m_socket, sendMassages);

    }

private:
    std::string  m_serverIp;
    uint16_t     m_serverPort;
    TCPSocketPtr m_socket;

};