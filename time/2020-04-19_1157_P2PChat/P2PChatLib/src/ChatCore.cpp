#include <thread>
#include "ChatCore.h"
#include "ChatException.hpp"
#include <chrono>
#include <thread>

void ChatCore::recieveLoop()
{
    while (m_connectionPoint->getStatus() == CpStatus::Connected)
    {
        auto msg = m_connectionPoint->receive();
        m_userInterface->setInboxMsg(msg);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }
}

ChatCore::ChatCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger)
{    
    m_connectionPoint = cp;
    m_userInterface = ui;
    m_logger = logger;
}

ChatCore::~ChatCore()
{

}

void ChatCore::start(std::string type, std::string connectInfo)
{
    if(type == "Server")
    {
        m_connectionPoint->accept(connectInfo);
    }
    else if (type == "Client")
    {
        m_connectionPoint->connect(connectInfo);
    }
    else
    {
        throw ChatException("Error: wrong type in ChatCore::start. Param = " + type
            + ". Expect Server or Client");
    }

    std::thread recieveThread(&ChatCore::recieveLoop, this);

    while (m_connectionPoint->getStatus() == CpStatus::Connected)
    {
        auto msg = m_userInterface->getUserInput();
        m_connectionPoint->send(msg);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }

    recieveThread.join();

    if(m_connectionPoint->getStatus() == CpStatus::Connected)
    {
        m_connectionPoint->disconnect();
    }
    else if(m_connectionPoint->getStatus() == CpStatus::ConnectionError)
    {
        throw ChatException("Error: Found connection error in ChatCore::Start()");
    }    
}