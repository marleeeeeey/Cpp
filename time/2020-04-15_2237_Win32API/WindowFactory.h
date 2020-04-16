#pragma once

#include "IBaseWindow.h"
#include <memory>
#include <string>

class WindowFactory
{
public:
    WindowFactory() {}
    std::shared_ptr<IBaseWindow> Create(std::string windowName);
};