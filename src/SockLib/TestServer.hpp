#include "StdPlus/StdPlus.h"
#include "TcpSocket.hpp"

class ClientManager
{
public:
    ClientManager()
    {

    }

    ~ClientManager()
    {

    }
    
    void updateClientsFrom(std::vector<Socket *> clients)
    {
        m_allClients = clients;
    }
    
    // TODO
    // calc unworking
    // calc remove

private:
    std::vector<Socket *> m_workingClients;
    std::vector<Socket *> m_allClients;

};

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

            int a;
            ABIND_INT(a, 0);
            if (a > 0)
            {
                sf.stopListen();
                break;
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