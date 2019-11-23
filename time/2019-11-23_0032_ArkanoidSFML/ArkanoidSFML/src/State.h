#pragma once
#include <SFML/Graphics.hpp>

class State
{
    bool m_destroyFlag = false;
    sf::Time m_timeStep;
    sf::RectangleShape m_collisionRect;

public:
    sf::RectangleShape getCollisionRect() const;
    void setCollisionRect(const sf::RectangleShape& collisionRect);
    void setPos(const sf::Vector2f& pos);
    sf::Vector2f getPos() const;
    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;
    void setDestroyFlag(bool isDestroyed);
    bool getDestroyFlag() const;
    void settimeStep(const sf::Time& timeStep);
    sf::Time gettimeStep() const;
};
