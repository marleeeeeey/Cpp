#pragma once
#include "IObject.h"

class DefaultObject : public IObject
{
protected:
    State m_state;

public:
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(sf::Event event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
    State getState() override;
    void setState(const State& state) override;
};
