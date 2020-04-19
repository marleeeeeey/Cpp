#pragma once

#include <string>
#include <memory>

class IUserInterface
{
public:
    virtual ~IUserInterface() = default;
    virtual std::string getUserInput() = 0;
    virtual void setInboxMsg(std::string msg) = 0;
};

using IUserInterfacePtr = std::shared_ptr<IUserInterface>;