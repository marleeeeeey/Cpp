#include "Brick.h"
#include "HelperFunctions.h"
#include "IObjectFactory.h"

Brick::Brick()
{
    m_lives = 1;
    m_appearanceNumber = 1;
}

void Brick::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    const std::vector<sf::Color> colors
    {
        sf::Color::Red,
        sf::Color::Cyan,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color::White,
    };
    auto colorIndex = m_appearanceNumber % colors.size();
    shape.setFillColor(colors[colorIndex]);
    window.draw(shape);
}

void Brick::onBumping(std::vector<Collision>& collisions)
{
    if (m_lives && m_lives.value() < 1)
    {
        state().setDestroyFlag(true);
    }
}

std::optional<int>& Brick::lives()
{
    return m_lives;
}

void Brick::setAppearance(int appearanceNumber)
{
    m_appearanceNumber = appearanceNumber;
}

std::optional<BonusType>& Brick::bonusType()
{
    return m_bonusType;
}

std::shared_ptr<IObject> Brick::createCopyFromThis()
{
    auto createdObjectPtr = std::make_shared<Brick>();
    Brick& createdObject = *createdObjectPtr.get();
    createdObject = *this;
    return createdObjectPtr;
}
