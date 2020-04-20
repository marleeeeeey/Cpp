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
        if(!msg.empty())
        {
            m_userInterface->setInboxMsg("[FRIEND]: " + msg);
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }
}

void ChatCore::sendLoop()
{
    while (m_connectionPoint->getStatus() == CpStatus::Connected)
    {
        auto msg = m_userInterface->getUserInput();
        m_connectionPoint->send(msg);
    }
}

ChatCore::ChatCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger)
{    
    m_connectionPoint = cp;
    m_userInterface = ui;
    m_logger = logger;

    m_logger->LogInfo("P2PChat v1.0 started");
}

ChatCore::~ChatCore()
{

}

void ChatCore::start()
{
    auto ci = m_userInterface->getConnectionInfo();
    if(ci.side == ConnectionInfo::Side::Server)
    {
        m_connectionPoint->accept(ci);
    }
    else if (ci.side == ConnectionInfo::Side::Client)
    {
        m_connectionPoint->connect(ci);
    }
    else
    {
        throw ChatException("Error: ChatCore::start connectioInfo");
    }

    std::thread recieveThread(&ChatCore::recieveLoop, this);    
    sendLoop();    
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
