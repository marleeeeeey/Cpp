#include "StdPlus/StdPlus.h"
#include "TcpSocket.hpp"

int main()
{
    AMSG("hello from TestServer");

    try
    {
        SocketFactory sf;
        sf.startListenPortInOtherThread(100);
        while (true)
        {
            if (sf.isClientsUpdate())
            {
                AMSG("clients update");
                for (Socket * client : sf.getClients())
                {
                    AVAR(*client);
                }
            }

            stdplus::thread_sleep(1000);
        }
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