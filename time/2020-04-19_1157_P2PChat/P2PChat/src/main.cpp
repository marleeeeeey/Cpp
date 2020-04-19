#include "P2PChatLib\DefaultFactory.h"
#include "P2PChatLib\ChatCore.h"


int main()
{
    DefaultFactory factory;

    auto cp = factory.createConnectionPoint("");
    auto ui = factory.createUserInterface("");
    auto lg = factory.createLogger("");

    ChatCore chat(cp, ui, lg);
    chat.start("Server", "ConnectInfo");
}