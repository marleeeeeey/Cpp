#pragma once
#include <memory>

class IPaddleController
{
public:
    virtual bool isPaddleUp() const = 0;
    virtual bool isPaddleDown() const = 0;
};

enum class ControllerType { Bot, User };


class ControllerFactory
{
    

public:
    std::shared_ptr<IPaddleController> getPaddleController(ControllerType controllerType);
};