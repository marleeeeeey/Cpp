#pragma once

//#include "ChatInclude.h"
#include "StdPlus/StdPlus.h"

class ChatServer
{
public:
    ChatServer()
    {

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
    }

private:
    std::string m_bindIp;
    uint16_t    m_bindPort;
    int         m_backlog;


};
