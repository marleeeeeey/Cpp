#pragma once

#include <string>

struct ConnectionInfo
{
    enum class Side { Server, Client } side;
    enum class Type { TCP } type;
    std::string ipV4_ip_port;
};
