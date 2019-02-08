#include <iostream>
#include "ServerInterface.h"
#include <future>

class Server
{
    std::vector<SocketPtr> clients;
    std::mutex clientsMtx;

    void waitClient(unsigned short port)
    {
        sf::TcpListener listener;
        if(listener.listen(port) != sf::Socket::Done)
            throw std::logic_error("can't access to port");
        std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

        while (true)
        {
            auto socket = std::make_shared<sf::TcpSocket>();
            if(listener.accept(*socket) != sf::Socket::Done)
                throw std::logic_error("error during connection to user");
            std::cout << "Client connected: " << socket->getRemoteAddress() << std::endl;
            onNewClient(socket);
        }
    }

    void onNewClient(SocketPtr client)
    {
        {
            std::lock_guard<std::mutex> lockClients(clientsMtx);
            clients.push_back(client);
            std::cout << "count of clients is " << clients.size() << std::endl;            
        }

        doInteraction(client);
    }

    void doInteraction(SocketPtr client)
    {
        sf::Packet packet;
        std::string msgToClient = "Hi, I'm the server";
        packet << msgToClient;
        client->send(packet);
        std::cout << "Message sent to the client: \"" << msgToClient << "\"" << std::endl;

        std::string msgFromClient;
        client->receive(packet);
        packet >> msgFromClient;
        std::cout << "Answer received from the client: \"" << msgFromClient << "\"" << std::endl;
    }

public:
    void runTcpServer(unsigned short port)
    {
        waitClient(port);
        std::async(&Server::waitClient, this, port);
    }
};

int main()
{
    Server s;
    s.runTcpServer(MagicNumbers::port());
    std::cin.get();
}