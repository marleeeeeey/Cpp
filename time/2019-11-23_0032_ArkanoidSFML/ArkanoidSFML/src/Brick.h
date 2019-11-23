#pragma once
#include "DefaultObject.h"

class Brick : public DefaultObject
{
public:
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
    void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) override;
};
