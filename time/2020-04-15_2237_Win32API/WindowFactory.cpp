#include "WindowFactory.h"
#include "MainWindow.h"
#include "DrawingWindow.h"
#include <stdexcept>

std::shared_ptr<IBaseWindow> WindowFactory::Create(std::string windowName)
{
    if (windowName == "MainWindow")
    {
        auto ptr = std::make_shared<MainWindow>();
        return ptr;
    }

    if (windowName == "DrawingWindow")
    {
        auto ptr = std::make_shared<DrawingWindow>();
        return ptr;
    }

    throw std::logic_error("Unknown name of window");
}
