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
    
    void updateClientsFrom(std::vector<Socket *> allClients)
    {
        AFUN;
        AVAR(m_workingClients.size());
        AVAR(allClients.size());

        std::sort(m_workingClients.begin(), m_workingClients.end());
        std::sort(allClients.begin(), allClients.end());

        std::vector<Socket *> newClients(
            (std::max)(m_workingClients.size(), allClients.size()));

        auto it = std::set_difference(
            allClients.begin(), allClients.end(),
            m_workingClients.begin(), m_workingClients.end(), 
            newClients.begin());

        newClients.resize(it - newClients.begin());

        AVAR(newClients.size());

        for (Socket * newClient : newClients)
        {
            runOnNewClient(newClient);
        }
    }
    
    void runOnNewClient(Socket * client)
    {
        AFUN;
        AVAR(client);
    }

    // TODO
    // calc unworking
    // calc remove

private:
    std::vector<Socket *> m_workingClients;

};

int main()
{
    AMSG("hello from TestServer");

    try
    {
        ClientManager cm;
        SocketFactory sf;
        sf.startListenPortInOtherThread(100);
        while (true)
        {
            if (sf.isClientsUpdate())
            {
                AMSG("clients update");
                std::vector<Socket *> allClients = sf.getClients();
                cm.updateClientsFrom(allClients);

//                 for (Socket * client : allClients)
//                 {
//                     AVAR(*client);
//                 }

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