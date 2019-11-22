#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Collision.h"

class IObject
{
public:
    virtual ~IObject() = default;
    virtual void onBumping(std::vector<Collision>& collisions) = 0;
    virtual void calcState(sf::Event event, sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual State getState() = 0;
    virtual void setState(const State& state) = 0;
};
