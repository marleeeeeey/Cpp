#include <iostream>
#include "ServerInterface.h"
#include <future>

class Server
{
    std::vector<SocketPtr> clients;
    std::mutex clientsMtx;
    int countMessage = 0;

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
            auto result(std::async(&Server::onNewClient, this, socket));
        }
    }

    void onNewClient(SocketPtr client)
    {
        {
            std::lock_guard<std::mutex> lockClients(clientsMtx);
            clients.push_back(client);
            std::cout << "count of clients is " << clients.size() << std::endl;            
        }

        clientLoop(client);
    }

    void clientLoop(SocketPtr client)
    {
        while (true)
        {
            static int counter = 0;
            std::cout << "counter=" << counter++ << std::endl;

            sf::Packet packet;
            client->receive(packet);
            ServerCmd cmd;
            packet >> cmd;
            countMessage++;
            switch(cmd)
            {
            case ServerCmd::RequestStatus:
            {
                packet.clear();
                ServerStatus ss = { clients.size(), countMessage };
                packet << ss;
                std::cout << ss << std::endl;
                client->send(packet);
            }
            break;
            case ServerCmd::MsgBroadcast: break;
            case ServerCmd::MsgToClient: break;
            default:;
            }            
        }
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
    }
};

int main()
{
    Server s;
    s.runTcpServer(MagicNumbers::port());
    std::cin.get();
}