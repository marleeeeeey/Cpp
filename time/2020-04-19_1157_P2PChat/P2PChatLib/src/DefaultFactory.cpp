#include "DefaultFactory.h"
#include "SocketConnectionPoint.h"
#include "DefaultUI.h"
#include "DefaultLogger.h"

IConnectionPointPtr DefaultFactory::createConnectionPoint(std::string msg, ILoggerPtr logger)
{
    return std::make_shared<SocketConnectionPoint>(logger);
}

ILoggerPtr DefaultFactory::createLogger(std::string logFilePath)
{
    return std::make_shared<DefaultLogger>(logFilePath);
}

IUserInterfacePtr DefaultFactory::createUserInterface(std::string msg, ILoggerPtr logger)
{
    return std::make_shared<DefaultUI>();
}
