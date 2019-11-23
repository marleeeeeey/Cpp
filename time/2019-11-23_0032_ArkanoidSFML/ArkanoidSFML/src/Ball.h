#pragma once
#include "DefaultObject.h"

class Ball : public DefaultObject
{
    sf::Vector2f m_speed;
    std::optional<Collision> m_biggestCollision;
    std::optional<State> m_lastNonCollisionState;

public:
    Ball();
    void onBumping(std::vector<Collision>& collisions) override;
    void debugFunControlBall(std::optional<sf::Event> event);
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
