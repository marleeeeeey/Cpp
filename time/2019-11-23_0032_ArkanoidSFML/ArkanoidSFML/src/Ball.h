#pragma once
#include "DefaultObject.h"

class Ball : public DefaultObject
{
    sf::Vector2f m_speed;
    float m_radius;
    sf::RectangleShape m_collisionRect;
    sf::CircleShape m_drawShape;

public:
    Ball();
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(sf::Event event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
