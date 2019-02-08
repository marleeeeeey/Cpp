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