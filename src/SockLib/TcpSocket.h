#ifndef SockLib_h__
#define SockLib_h__

#include "StdPlus/StdPlus.h"    
#include "StdPlus/SockLibPlus.hpp"

typedef int RawSocket;

class Socket
{
    friend std::ostream & operator<<(std::ostream & os, const Socket & p);

public:
    Socket(RawSocket rawSocket, const std::string & ip, int port)
        : m_socket(rawSocket)
        , m_ip(ip)
        , m_port(port)
    {

    }

    ~Socket()
    {
        try
        {
            stop();
        }
        catch (std::logic_error & exStopSocket)
        {
            AVAR(exStopSocket.what());
        }
    }

    int recv(void *buf, int size)
    {
        using namespace stdplus;

        int sizeRead_byte = sl_read(m_socket, buf, size);

        if (sizeRead_byte < 0)
            throw std::logic_error(sl_error_str(sizeRead_byte));

        return sizeRead_byte;
    }

    int send(const void *buf, int size)
    {
        using namespace stdplus;

        int sizeSend_byte = sl_write(m_socket, buf, size);

        if (sizeSend_byte < 0)
            throw std::logic_error(sl_error_str(sizeSend_byte));

        return sizeSend_byte;
    }

private:
    void stop()
    {
        using namespace stdplus;

        int result = sl_disconnect(m_socket);

        if (result < 0)
            throw std::logic_error(sl_error_str(result));
    }

    RawSocket   m_socket;
    std::string m_ip;
    int         m_port           = 0;
    unsigned    m_totalRecv_byte = 0;
    unsigned    m_totalSend_byte = 0;
};

std::ostream & operator<<(std::ostream & os, const Socket & s)
{
    os
        << "id="        << s.m_socket         << "; "
        << "ip="        << s.m_ip             << "; "
        << "port="      << s.m_port           << "; "
        << "totalRecv=" << s.m_totalRecv_byte << "; "
        << "totalSend=" << s.m_totalSend_byte << "; "
        ;

    return os;
}

class SocketFactory
{
public:
    SocketFactory()
    {
        int & counter = instanseCounter();

        if (counter == 0)
            stdplus::sl_init();

        counter++;
    }

    ~SocketFactory()
    {
        stopListen();

        int & counter = instanseCounter();

        if (counter > 0)
        {
            counter--;

            if (counter == 0)
                stdplus::sl_term();
        }
    }

    Socket connectToServer(std::string serverIp, int serverPort)
    {
        using namespace stdplus;

        int result = sl_connect_to_server(serverIp.c_str(), serverPort);

        if (result < 0)
            throw std::logic_error(sl_error_str(result));

        RawSocket rawSocket = result;

        return Socket(rawSocket, serverIp, serverPort);
    }

    void startListenPort(int port, int backlog = 1)
    {
        AFUN;

        using namespace stdplus;

        int result = sl_make_server_socket_ex(
            "0.0.0.0", port, backlog, m_isNonBlockMode);

        if (result < 0)
            throw std::logic_error(sl_error_str(result));

        RawSocket rawServerSocket = result;

        stopListen();
        m_isListening = true;
        AVAR(m_isListening);

        m_listenThread = std::thread(
            &SocketFactory::listenCycle, this, rawServerSocket, port);
    }

    void stopListen()
    {
        if (!m_isListening)
            return;

        m_isListening = false;

        if (m_listenThread.joinable())
            m_listenThread.join();

        AVAR(m_isListening);
    }

    std::vector<Socket> getClients() 
    {
        std::lock_guard<std::mutex> guard(m_mutexClients);
        m_isClientsUpdate = false;
        return m_clients;
    }

    bool isClientsUpdate() const { return m_isClientsUpdate; }

private:
    void listenCycle(RawSocket rawServerSocket, int port)
    {
        AFUN;

        using namespace stdplus;

        while (m_isListening)
        {
            int result = 0;
            unsigned rawIpAdress;

            result = sl_select(rawServerSocket, m_timeout_ms);

            result = sl_accept(rawServerSocket, &rawIpAdress);
            
            if (result < 0)
            {
                if (m_isNonBlockMode)
                {
                    AMSG("Wait listner timeout. " + to_string(sl_error_str(result)));
                    continue;
                }
                else
                    throw std::logic_error(sl_error_str(result));
            }

            RawSocket rawSocket = result;
            std::string ip = sl_inet_ntoa(rawIpAdress);
            Socket clientSocket = Socket(rawSocket, ip, port);

            AVAR(clientSocket);
            std::lock_guard<std::mutex> guard(m_mutexClients);
            m_clients.push_back(clientSocket);

            m_isClientsUpdate = true;

        }

    }

    int & instanseCounter() 
    {
        static int counter = 0;
        return counter;
    }

    int                 m_timeout_ms      = 1000;
    bool                m_isNonBlockMode  = true;

    bool                m_isListening     = false;
    bool                m_isClientsUpdate = false;
    std::mutex          m_mutexClients;
    std::vector<Socket> m_clients;
    std::thread         m_listenThread;
};


#endif // SockLib_h__
