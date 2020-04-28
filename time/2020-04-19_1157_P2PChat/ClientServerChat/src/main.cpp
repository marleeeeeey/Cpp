#include <sstream>

#include "DefaultFactoryLib\DefaultFactory.h"
#include "CSChatCore.h"
#include "ChatITF\ChatException.hpp"


int main(int argc, char** argv)
{
    std::vector<std::string> cmdLines;
    for (int i = 0; i < argc; ++i)
    {
        cmdLines.push_back(argv[i]);
    }

    DefaultFactory factory;
    auto lg = factory.createLogger("logs/" + cmdLines[1] + ".log");
    auto cp = factory.createConnectionPoint("", lg);
    auto ui = factory.createUserInterface(cmdLines, lg);

    try
    {
        CSChatCore chat(cp, ui, lg);
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
