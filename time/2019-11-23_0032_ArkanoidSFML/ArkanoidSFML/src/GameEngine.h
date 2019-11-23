#pragma once
#include "IWorld.h"
#include "ObjectFactory.h"
#include <optional>

class GameEngine
{
    std::shared_ptr<IWorld> m_world;

public:
    GameEngine(std::shared_ptr<IWorld> world);
    void setEvent(std::optional<sf::Event> event, sf::Time timeStep);
    void draw(sf::RenderWindow& window);
};
