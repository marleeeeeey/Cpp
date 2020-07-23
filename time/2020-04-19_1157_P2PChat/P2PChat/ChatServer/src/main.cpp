#include <sstream>

#include "DefaultFactoryLib\DefaultFactory.h"
#include "ServerCore.h"
#include "ChatITF\ChatException.hpp"


int main(int argc, char** argv)
{
    std::vector<std::string> cmdLines
    {
        argv[0],
        "Server",
        argv[1],
    };

    DefaultFactory factory;
    auto lg = factory.createLogger("logs/ChatServer.log");
    auto ui = factory.createUserInterface(cmdLines, lg);

    try
    {
        ServerCore chat(ui, lg);
        chat.start();
    }
    catch (const ChatException& e)
    {
        lg->LogError(std::string("ChatException: ") + e.what());
        return 1;
    }
    catch (const std::exception& e)
    {
        lg->LogError(std::string("std::exception: ") + e.what());
        return 1;
    }
    catch (...)
    {
        lg->LogError("Unknown Exception");
        return 1;
    }

    return 0;
}
