#include "StdPlus/StdPlus.h"
#include "TcpSocket.h"

int main()
{
    AMSG("hello from TestSockLib");

    try
    {
        SocketFactory sf;
        sf.startListenPort(10);
        AMSG("press any key for stop listen port");
        APAUSE;
        sf.stopListen();
        APAUSE;
    }
    catch (std::logic_error & e)
    {
        AVAR(e.what());
    }

    APAUSE;
}