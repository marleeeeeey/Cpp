#include "ClientCore.h"
#include <chrono>
#include <thread>
#include "ChatITF\ChatException.hpp"

void ClientCore::receiveLoop()
{
    while (m_connectionPoint->getStatus() == CpStatus::Connected)
    {
        auto msg = m_connectionPoint->receive();
        if (!msg.empty())
        {
            m_userInterface->setInboxMsg("[FRIEND]: " + msg);
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    }
}

void ClientCore::sendLoop()
{
    while (m_connectionPoint->getStatus() == CpStatus::Connected)
    {
        auto msg = m_userInterface->getUserInput();
        m_connectionPoint->send(msg);
    }
}

ClientCore::ClientCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger)
{
    m_connectionPoint = cp;
    m_userInterface = ui;
    m_logger = logger;

    m_logger->LogInfo("ChatClient v0.1 started");
}

void ClientCore::start()
{
    auto ci = m_userInterface->getConnectionInfo();
    m_connectionPoint->connect(ci);

    std::thread receiveThread(&ClientCore::receiveLoop, this);
    sendLoop();
    receiveThread.join();

    if (m_connectionPoint->getStatus() == CpStatus::Connected)
    {
        m_connectionPoint->disconnect();
    }
    else if (m_connectionPoint->getStatus() == CpStatus::ConnectionError)
    {
        throw ChatException("Found connection error in ChatCore::Start()");
    }
}
