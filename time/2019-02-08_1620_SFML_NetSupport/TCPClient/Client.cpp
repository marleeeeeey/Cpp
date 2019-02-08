#include <iostream>
#include "ServerInterface.h"

void runTcpClient(unsigned short port)
{
    // Ask for the server address
    sf::IpAddress server;
    do
    {
        std::cout << "Type the address or name of the server to connect to: ";
        //std::cin >> server;
        server = "127.0.0.1";
    } while(server == sf::IpAddress::None);

    // Create a socket for communicating with the server
    sf::TcpSocket socket;

    // Connect to the server
    if(socket.connect(server, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << server << std::endl;

    sf::Packet packet;

    std::string msgFromServer;
    socket.receive(packet);
    packet >> msgFromServer;
    std::cout << "Answer received from the server: \"" << msgFromServer << "\"" << std::endl;

    std::string msgToServer = "Hi, I'm the client";
    packet << msgToServer;
    socket.send(packet);
    std::cout << "Message sent to the server: \"" << msgToServer << "\"" << std::endl;
}

int main()
{
    runTcpClient(MagicNumbers::port());
    std::cin.get();
}