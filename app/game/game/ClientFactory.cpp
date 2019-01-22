#include "stdafx.h"
#include "ClientFactory.h"
#include <SFML/Window/Keyboard.hpp>
#include "ServerPackage.h"
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <SFML/System/Clock.hpp>

class KeyboardClient : public IClient
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

    void updateState() override {}
};

class BotClient : public IClient
{
    ServerPackage serverPackage;
    float rightPaddleSpeed = 0.f;
    enum class BotPaddleState { None, Up, Down };
    BotPaddleState state = BotPaddleState::None;

    // Define the paddles properties
    sf::Clock AITimer;
    const sf::Time AITime = sf::seconds(0.1f);

public:
    void setServerPackage(const ServerPackage& package) override { serverPackage = package; }
    
    bool paddleUp() const override
    {
        return state == BotPaddleState::Up;
    }

    bool paddleDown() const override
    {
        return state == BotPaddleState::Down;
    }

    void updateState() override
    {
        ServerPackage & sp = serverPackage;

        // Update the computer's paddle direction according to the ball position
        if (AITimer.getElapsedTime() > AITime)
        {
            AITimer.restart();
            if (sp.ballCenter.y + sp.ballRadius > sp.rightPaddleCenter.y + sp.rightPaddleSize.y / 2)
                state = BotPaddleState::Down;
            else if (sp.ballCenter.y - sp.ballRadius < sp.rightPaddleCenter.y - sp.rightPaddleSize.y / 2)
                state = BotPaddleState::Up;
            else
                state = BotPaddleState::None;
        }        
    }
};

std::shared_ptr<IClient> ClientFactory::createClient(ClientType controllerType)
{
    switch (controllerType)
    {
    case ClientType::User:
        return std::shared_ptr<IClient>(new KeyboardClient());
    case ClientType::Bot:
        return std::shared_ptr<IClient>(new BotClient());
    }

    if (controllerType==ClientType::User)
    {
    }

}
