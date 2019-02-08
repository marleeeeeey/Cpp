#include <SFML/Network.hpp>
#include <iostream>

void runTcpClient(unsigned short port)
{
    // Ask for the server address
    sf::IpAddress server;
    do
    {
        std::cout << "Type the address or name of the server to connect to: ";
        std::cin >> server;
    } while(server == sf::IpAddress::None);

    // Create a socket for communicating with the server
    sf::TcpSocket socket;

    // Connect to the server
    if(socket.connect(server, port) != sf::Socket::Done)
        return;
    std::cout << "Connected to server " << server << std::endl;

    // Receive a message from the server
    char in[128];
    std::size_t received;
    if(socket.receive(in, sizeof(in), received) != sf::Socket::Done)
        return;
    std::cout << "Message received from the server: \"" << in << "\"" << std::endl;

    // Send an answer to the server
    const char out[] = "Hi, I'm a client";
    if(socket.send(out, sizeof(out)) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
}

int main()
{
    runTcpClient(12345);
    std::cin.get();
}