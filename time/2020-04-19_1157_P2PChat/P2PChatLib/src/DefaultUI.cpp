#include <iostream>
#include "DefaultUI.h"


ConnectionInfo createConectioInfoFromCmdLines(std::vector<std::string> cmdLines)
{
    ConnectionInfo ci{};

    const std::map<std::string, ConnectionInfo::Side> sideMap
    {
        {"Server", ConnectionInfo::Side::Server},
        {"Client", ConnectionInfo::Side::Client},
    };

    ci.side = sideMap.at(cmdLines[1]);
    ci.ipV4_ip_port = cmdLines[2];

    return ci;
}

DefaultUI::DefaultUI(std::vector<std::string> cmdLines, ILoggerPtr logger)
{
    m_connectionInfo = createConectioInfoFromCmdLines(cmdLines);
    m_logger = logger;
}

std::string DefaultUI::getUserInput()
{
    std::string userInput;
    std::string prefix = "[YOU]: ";
    std::cout << prefix;
    std::getline(std::cin, userInput);
    m_logger->LogTrace(prefix + userInput);
    while (!m_inboxMsg.empty())
    {
        std::string msg = m_inboxMsg.front();
        m_inboxMsg.pop();
        std::cout << msg << std::endl;        
    }
    return userInput;
}

void DefaultUI::setInboxMsg(std::string msg)
{
    m_inboxMsg.push(msg);
    m_logger->LogTrace(msg);
}

ConnectionInfo DefaultUI::getConnectionInfo()
{
    return m_connectionInfo;
}
