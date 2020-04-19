#pragma once

#include "IUserInterface.h"

class DefaultUI : public IUserInterface
{
public:
    std::string getUserInput() override;
    void setInboxMsg(std::string msg) override;
};