#include "StdPlus/StdPlus.h"
#include "TcpSocket.hpp"

std::vector<Socket *> getSockets()
{
    std::vector<Socket *> sockets;

    std::vector<std::string> names
    {
        "Petya", "Vasya", "Masha", "Dasha",
        "Nika", "Natalia", "Anna", "Katya",
    };
    
    try
    {
        SocketFactory sf;
        for (int i = 0; i < 10; ++i)
        {
            Socket * sock = sf.connectToServer("127.0.0.1", 100);
            int index = i % names.size();
            sock->setName(names[index]);
            AVAR(*sock);
            sockets.push_back(sock);
            stdplus::thread_sleep(2000);
        }
    }
    catch (std::logic_error & e)
    {
        AVAR(e.what());
    }

    return sockets;
}

int main()
{
    AMSG("hello from TestClient");
    AMSG("press any key to start");
    APAUSE;

    getSockets();
    
    APAUSE;
}