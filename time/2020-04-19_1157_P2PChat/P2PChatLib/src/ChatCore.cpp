#include "ChatCore.h"

ChatCore::ChatCore(IConnectionPointPtr cp, IUserInterfacePtr ui, ILoggerPtr logger)
{
    m_connectionPoint = cp;
    m_userInterface = ui;
    m_logger = logger;
}

ChatCore::~ChatCore()
{
}

void ChatCore::start()
{

}
