#include "stdafx.h"
#include "ClientFactory.h"
#include <SFML/Window/Keyboard.hpp>

class UserPaddleController : public IClient
{
public:
    bool paddleUp() const override
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    }

    bool paddleDown() const override
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    }
};

std::shared_ptr<IClient> ClientFactory::createClient(ControllerType controllerType)
{
    if (controllerType==ControllerType::User)
    {
        return std::shared_ptr<IClient>(new UserPaddleController());
    }
}
