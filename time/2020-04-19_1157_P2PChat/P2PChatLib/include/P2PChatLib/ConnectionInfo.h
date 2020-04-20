#pragma once

#include <string>
#include <map>
#include <vector>

struct ConnectionInfo
{
    enum class Side { Server, Client } side;
    enum class Type { TCP } type;
    std::string ipV4_ip_port;
};
