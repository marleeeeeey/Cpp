#include <iostream>
#include <sstream>

#include "DefaultFactoryLib\DefaultFactory.h"
#include "ClientCore.h"
#include "ChatITF\ChatException.hpp"


int main(int argc, char** argv)
{
    std::vector<std::string> cmdLines
    {
        argv[0],
        "Client",
        argv[1],
    };

    DefaultFactory factory;
    auto lg = factory.createLogger("logs/ChatClient.log");
    auto cp = factory.createConnectionPoint("", lg);
    auto ui = factory.createUserInterface(cmdLines, lg);

    int ret = 0;

    try
    {
        ClientCore chat(cp, ui, lg);
        chat.start();
    }
    catch (const ChatException& e)
    {
        lg->LogError(std::string("ChatException: ") + e.what());
        ret = 1;
    }
    catch (const std::exception& e)
    {
        lg->LogError(std::string("std::exception: ") + e.what());
        ret = 1;
    }
    catch (...)
    {
        lg->LogError("Unknown Exception");
        ret = 1;
    }

    std::cout << "Press <ENTER> to close window";
    std::cin.get();
    return ret;
}
