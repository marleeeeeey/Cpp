#pragma once
#include "SFML/Graphics.hpp"

class IObject;

class Collision
{
    std::shared_ptr<IObject> m_object;
    sf::RectangleShape m_collisionRect;

public:
    Collision(std::shared_ptr<IObject> object, sf::RectangleShape collisionRect);
    Collision(const Collision& other) = default;
    std::shared_ptr<IObject> getObject();
    sf::RectangleShape getCollisionRect() const;
};
