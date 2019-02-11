#pragma once
#include <SFML/Network.hpp>

using SocketPtr = std::shared_ptr<sf::TcpSocket>;

class MagicNumbers
{
public:
    static unsigned short port() { return 12345; };
};

enum class ServerCmd 
{
    RequestStatus,
    MsgBroadcast,
    MsgToClient,
};


sf::Packet& operator <<(sf::Packet& packet, const ServerCmd& data)
{
    const int intCmd = static_cast<int>(data);
    return packet << intCmd;
}

sf::Packet& operator >>(sf::Packet& packet, ServerCmd& data)
{
    int intCmd;
    auto retVal = packet >> intCmd;
    data = static_cast<ServerCmd>(intCmd);
    return retVal;
}

struct ServerStatus
{
    int countClients;
    int countMessages;
};

sf::Packet& operator <<(sf::Packet& packet, const ServerStatus& data)
{
    return packet << data.countClients << data.countMessages;
}

sf::Packet& operator >>(sf::Packet& packet, ServerStatus& data)
{
    return packet >> data.countClients >> data.countMessages;
}

std::ostream & operator <<(std::ostream & os, const ServerStatus& data)
{
    os << "countClients=" << data.countClients << "; " << "countMessage=" << data.countMessages;
    return os;
}