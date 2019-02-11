#include <iostream>
#include "ServerInterface.h"

void runTcpClient(unsigned short port)
{
    sf::IpAddress serverIp = "127.0.0.1";
    sf::TcpSocket socket;

    if(socket.connect(serverIp, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << serverIp << std::endl;

    sf::Packet packet;

    while (true)
    {
        std::cout << "press any key to request to server" << std::endl;
        std::cin.get();
        ServerCmd cmd = ServerCmd::RequestStatus;
        packet << cmd;
        ServerStatus ss;
        packet >> ss;
        std::cout << ss << std::endl;
    }

    //std::string msgFromServer;
    //socket.receive(packet);
    //packet >> msgFromServer;
    //std::cout << "Answer received from the server: " << msgFromServer << std::endl;
    //
    //std::string msgToServer = "Hi, I'm the client";
    //packet << msgToServer;
    //socket.send(packet);
    //std::cout << "Message sent to the server: " << msgToServer << std::endl;
}

int main()
{
    runTcpClient(MagicNumbers::port());
    std::cin.get();
}