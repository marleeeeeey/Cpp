#include "stdafx.h"
#include "ControllerFactory.h"
#include <SFML/Window/Keyboard.hpp>

class UserPaddleController : public IPaddleController
{
public:
    bool isPaddleUp() const override
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    }

    bool isPaddleDown() const override
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    }
};

std::shared_ptr<IPaddleController> ControllerFactory::getPaddleController(ControllerType controllerType)
{
    if (controllerType==ControllerType::User)
    {
        return std::shared_ptr<IPaddleController>(new UserPaddleController());
    }
}
