#include "DefaultFactory.h"
#include "SocketConnectionPoint.h"
#include "DefaultUI.h"
#include "DefaultLogger.h"

IConnectionPointPtr DefaultFactory::createConnectionPoint(std::string msg)
{
    return std::make_shared<SocketConnectionPoint>();
}

ILoggerPtr DefaultFactory::createLogger(std::string msg)
{
    return std::make_shared<DefaultLogger>();
}

IUserInterfacePtr DefaultFactory::createUserInterface(std::string msg)
{
    return std::make_shared<DefaultUI>();
}
