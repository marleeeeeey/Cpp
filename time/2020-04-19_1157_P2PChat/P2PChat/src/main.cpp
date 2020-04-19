#include "P2PChatLib\DefaultFactory.h"
#include "P2PChatLib\ChatCore.h"
#include <sstream>

#include "P2PChatLib/ChatException.hpp"


int main(int argc, char ** argv)
{
    DefaultFactory factory;
    std::string type;
    std::string connectionInfo;

    if(argc == 3)
    {
        type = argv[1];
        connectionInfo = argv[2];
    }
    else
    {
        std::stringstream ss;
        ss << "Command line arguments error. Cout = " << argc
            << ". But expect 3. Example: P2PChat.exe Server 127.0.0.1:56710" << std::endl;
        auto lg = factory.createLogger("default.log");
        lg->LogError(ss.str());
        return 1;
    }

    auto lg = factory.createLogger(type + ".log");
    auto cp = factory.createConnectionPoint("", lg);
    auto ui = factory.createUserInterface("", lg);

    try
    {
        ChatCore chat(cp, ui, lg);
        chat.start(type, connectionInfo);
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
