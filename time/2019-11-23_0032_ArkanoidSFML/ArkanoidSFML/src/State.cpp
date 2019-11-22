#include "State.h"

sf::RectangleShape State::getCollisionRect() const
{
    return m_collisionRect;
}

void State::setCollisionRect(const sf::RectangleShape& collisionRect)
{
    m_collisionRect = collisionRect;
}

void State::setPos(const sf::Vector2f& pos)
{
    m_collisionRect.setPosition(pos);
}

sf::Vector2f State::getPos() const
{
    return m_collisionRect.getPosition();
}

void State::setSize(const sf::Vector2f& size)
{
    m_collisionRect.setSize(size);
}

sf::Vector2f State::getSize() const
{
    return m_collisionRect.getSize();
}

void State::setIsDestroyed(bool isDestroyed)
{
    m_isDestroyed = isDestroyed;
}

bool State::getIsDestroyed() const
{
    return m_isDestroyed;
}

void State::settimeStep(const sf::Time& timeStep)
{
    m_timeStep = timeStep;
}

sf::Time State::gettimeStep() const
{
    return m_timeStep;
}
