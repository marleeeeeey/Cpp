#include "P2PChatLib\DefaultFactory.h"
#include "P2PChatLib\ChatCore.h"
#include <sstream>

#include "P2PChatLib/ChatException.hpp"


int main(int argc, char ** argv)
{
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
            << ". But expect 3" << std::endl;
        throw std::logic_error(ss.str());
    }

    DefaultFactory factory;
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
    }
    catch (const std::exception & e)
    {
        lg->LogError(std::string("std::exception: ") + e.what());
    }
    catch(...)
    {
        lg->LogError("Unknown Exception");        
    }
}
