#include <iostream>
#include "DefaultUI.h"


std::string DefaultUI::getUserInput()
{
    std::string userInput;
    std::cout << "Input msg: ";
    std::cin >> userInput;
    return userInput;
}

void DefaultUI::setInboxMsg(std::string msg)
{
    std::cout << msg << std::endl;
}
