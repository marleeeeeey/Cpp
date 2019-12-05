#include "Brick.h"
#include "HelperFunctions.h"
#include "IObjectFactory.h"

Brick::Brick()
{
    m_lives = 1;
}

void Brick::draw(sf::RenderWindow& window)
{
    sf::Color shapeColor;
    if (!m_lives)
    {
        shapeColor = sf::Color::Cyan;
    }
    else if (m_bonusType)
    {
        shapeColor = sf::Color::Red;
    }
    else
    {
        const std::vector<sf::Color> livesColor
        {
            sf::Color::White,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Green,
            sf::Color::Magenta,
        };

        auto colorIndex = m_lives.value() % livesColor.size();
        shapeColor = livesColor.at(colorIndex);
    }
    auto shape = state().getCollisionRect();
    shape.setFillColor(shapeColor);
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
