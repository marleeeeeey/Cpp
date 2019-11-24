#pragma once
#include "DefaultObject.h"

class Plate : public DefaultObject
{
    float m_speed;
    std::optional<State> m_lastNonCollisionState;

public:
    Plate(std::shared_ptr<IObjectFactory> objectFactory);
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
};
