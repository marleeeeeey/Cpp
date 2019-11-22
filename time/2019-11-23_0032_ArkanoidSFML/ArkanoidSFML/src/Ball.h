#pragma once
#include "DefaultObject.h"

class Ball : public DefaultObject
{
public:
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(sf::Event event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
