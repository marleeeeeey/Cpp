#pragma once
#include "IObject.h"

class DefaultObject : public IObject
{
    State m_state;

public:
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    State& state() override;
};
