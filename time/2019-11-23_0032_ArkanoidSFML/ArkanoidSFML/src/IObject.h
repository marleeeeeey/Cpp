#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Collision.h"
#include <optional>

class IObjectFactory;

class IObject : public std::enable_shared_from_this<IObject>
{
public:
    virtual ~IObject() = default;
    virtual void onBumping(std::vector<Collision>& collisions) = 0;
    virtual void calcState(std::optional<sf::Event> event, sf::Time elapsedTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual std::optional<std::vector<IObject>> getChildren() = 0;
    virtual State& state() = 0;
    virtual std::shared_ptr<IObjectFactory> getObjectFactory() = 0;
};
