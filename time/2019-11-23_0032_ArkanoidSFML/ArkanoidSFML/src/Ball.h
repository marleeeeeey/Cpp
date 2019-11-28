#pragma once
#include "DefaultObject.h"
#include "MathVector.h"

class Ball : public DefaultObject
{
    MathVector m_speed;
    std::optional<Collision> m_biggestCollision;
    std::optional<State> m_lastNonCollisionState;

public:
    Ball();
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
