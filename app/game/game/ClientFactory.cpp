#include "stdafx.h"
#include "ClientFactory.h"
#include <SFML/Window/Keyboard.hpp>
#include "ServerPackage.h"
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <SFML/System/Clock.hpp>
#include <cctype>

sf::Keyboard::Key getKeyFromChar(char letter)
{
    letter = std::toupper(letter);
    const auto offset = 'A';
    return static_cast<sf::Keyboard::Key>(letter - offset);
}

class KeyboardClient : public IClient
{
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;

public:
    KeyboardClient(const sf::Keyboard::Key up, const sf::Keyboard::Key down)
    {
        this->up = up;
        this->down = down;        
    }

    // interface IClient
    bool paddleUp() const override
    {
        return sf::Keyboard::isKeyPressed(up);
    }

    bool paddleDown() const override
    {
        return sf::Keyboard::isKeyPressed(down);
    }

    void updateState() override {}

};

class BotClient : public IClient
{
    ServerPackage serverPackage{};
    float rightPaddleSpeed = 0.f;
    enum class BotPaddleState { None, Up, Down };
    BotPaddleState state = BotPaddleState::None;

    // Define the paddles properties
    sf::Clock timer;
    const sf::Time timerThreshold = sf::seconds(0.1f);

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
        auto& sp = serverPackage;

        // Update the computer's paddle direction according to the ball position
        if (timer.getElapsedTime() > timerThreshold)
        {
            timer.restart();
            if (sp.ballCenter.y + sp.ballRadius > sp.rightPaddleCenter.y + sp.rightPaddleSize.y / 2)
                state = BotPaddleState::Down;
            else if (sp.ballCenter.y - sp.ballRadius < sp.rightPaddleCenter.y - sp.rightPaddleSize.y / 2)
                state = BotPaddleState::Up;
            else
                state = BotPaddleState::None;
        }        
    }
};

std::shared_ptr<IClient> ClientFactory::createClient(const ClientType controllerType, std::string params) const
{
    switch (controllerType)
    {
    case ClientType::User:
        assert(!params.empty());
        return std::static_pointer_cast<IClient>(
            std::make_shared<KeyboardClient>(getKeyFromChar(params[0]), getKeyFromChar(params[1])));
    case ClientType::Bot:
        return std::static_pointer_cast<IClient>(std::make_shared<BotClient>());
    }

    return {};
}
