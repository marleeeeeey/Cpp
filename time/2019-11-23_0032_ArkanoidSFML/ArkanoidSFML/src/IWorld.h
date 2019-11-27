#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class IWorld
{
public:
    virtual ~IWorld() = default;
    virtual void updateState(std::optional<sf::Event> event, sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};
