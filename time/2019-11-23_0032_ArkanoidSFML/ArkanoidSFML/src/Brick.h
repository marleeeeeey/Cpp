#pragma once
#include "DefaultObject.h"

class Brick : public DefaultObject
{
public:
    Brick(std::shared_ptr<IObjectFactory> objectFactory);
    void draw(sf::RenderWindow& window) override;
    void onBumping(std::vector<Collision>& collisions) override;
};
