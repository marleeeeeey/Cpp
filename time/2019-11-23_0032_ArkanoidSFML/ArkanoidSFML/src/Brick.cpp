#include "Brick.h"
#include "HelperFunctions.h"
#include "IObjectFactory.h"

Brick::Brick()
{
    m_lives = 1;
    m_appearanceNumber = 0;
}

void Brick::draw(sf::RenderWindow& window)
{
    auto shape = state().getCollisionRect();
    const std::vector<sf::Color> colors
    {
        sf::Color::Red,
        sf::Color::Blue,
        sf::Color::Yellow,
    };
    auto colorIndex = m_appearanceNumber % colors.size();
    shape.setFillColor(colors[colorIndex]);
    window.draw(shape);
}

void Brick::onBumping(std::vector<Collision>& collisions)
{
    state().setDestroyFlag(true);
}

void Brick::setLives(int lives)
{
    m_lives = lives;
}

void Brick::setAppearance(int appearanceNumber)
{
    m_appearanceNumber = appearanceNumber;
}

void Brick::setBonusType(std::optional<BonusType> bonusType)
{
    m_bonusType = bonusType;
}

std::optional<BonusType> Brick::getBonusType()
{
    return m_bonusType;
}
