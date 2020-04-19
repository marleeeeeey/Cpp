#include <iostream>
#include "DefaultUI.h"


DefaultUI::DefaultUI(ILoggerPtr logger)
{
    m_logger = logger;
}

std::string DefaultUI::getUserInput()
{
    std::string userInput;
    std::string prefix = "[YOU]: ";
    std::cout << "[YOU]: ";
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
