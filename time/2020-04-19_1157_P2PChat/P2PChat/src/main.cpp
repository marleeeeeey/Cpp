#include "P2PChatLib\DefaultFactory.h"
#include "P2PChatLib\ChatCore.h"
#include <sstream>

#include "P2PChatLib/ChatException.hpp"


int main(int argc, char ** argv)
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
        ChatCore chat(cp, ui, lg);
        chat.start();
    }
    catch (const ChatException& e)
    {
        lg->LogError(std::string("ChatException: ") + e.what());
        return 1;
    }
    catch (const std::exception & e)
    {
        lg->LogError(std::string("std::exception: ") + e.what());
        return 1;
    }
    catch(...)
    {
        lg->LogError("Unknown Exception");
        return 1;
    }

    return 0;
}
