#pragma once

#include <exception>
#include <string>

class ChatException : public std::exception
{
public:
    ChatException(std::string msg)
        : std::exception(msg.c_str())
    { }
};
