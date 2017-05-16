#include "RoboCatPCH.h"

#include "StdPlus/StdPlus.h"

int main(int argc, const char** argv)
{
    //SocketUtil::StaticInit();

    auto sock = SocketUtil::CreateTCPSocket(INET);
//     SocketAddress recievingAdresses(INADDR_ANY, 48000);
//     auto bindResult = sock->Bind(recievingAdresses);
// 
//     AVAR(bindResult);

    AVAR(sock);
    APAUSE;

    SocketUtil::CleanUp();
}

