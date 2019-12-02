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
    m_lives--;
    if(m_lives < 1)
    {
        state().setDestroyFlag(true);        
    }
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
