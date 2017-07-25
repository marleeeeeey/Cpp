#pragma once

#include "OopSocket/OopSocket.h"
#include "StdPlus/StdPlus.h"

int main(int argc, char ** argv)
{
    LOG_STD_REGISTER_STREAM(std::cout);

    LOG_STD_MSG("Hello from TcpReciever");
    stdplus::CmdParser cmd;
    cmd.parseData(argc, argv);
    
    std::string listenIp = cmd.getValue<std::string>("ip", "127.0.0.1");
    int port = cmd.getValue<int>("port", 34567);

    LOG_STD_VAR(listenIp);
    LOG_STD_VAR(port);

    SocketUtil::StaticInit();

    TCPSocketPtr sock = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
    LOG_STD_MSG("listen socket created");
    SocketAddress sa(listenIp, port);
    sock->Bind(sa);
    LOG_STD_MSG("bind OK");
    sock->Listen();
    LOG_STD_MSG("listen OK");
    SocketAddress clientAddr;
    TCPSocketPtr clientSock = sock->Accept(clientAddr);
    LOG_STD_MSG("accept OK");

    clientSock->SetNonBlockingMode(true);
    LOG_STD_VAR(clientAddr);

    for (int i = 0; i < 100; ++i)
    {
        LOG_STD_VAR(i);
        char ch;
        try
        {
            clientSock->Receive(&ch, sizeof(ch));
        }
        catch (std::logic_error & e)
        {
            LOG_STD_MSG(e.what());
        }
        LOG_STD_VAR(ch);
    }

    SocketUtil::CleanUp();

    APAUSE;
}