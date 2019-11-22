#pragma once
#include <SFML/Graphics.hpp>

class IWorld
{
public:
    virtual ~IWorld() = default;
    virtual void generate() = 0;
    virtual bool isGameOver() = 0;
    virtual void updateState(sf::Event event, sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};
