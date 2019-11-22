#pragma once
#include "IObjectFactory.h"
#include "IWorld.h"

class World : public IWorld
{
    sf::Vector2f m_worldSize;
    std::shared_ptr<IObjectFactory> m_objectFactory;
    std::vector<std::shared_ptr<IObject>> m_matrix;
    std::vector<std::shared_ptr<IObject>> m_walls;
    std::vector<std::shared_ptr<IObject>> m_balls;
    std::vector<std::shared_ptr<IObject>> m_plates;

public:
    World(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize);
    void generate() override;
    bool isGameOver() override;
    void updateState(sf::Event event, sf::Time elapsedTime) override;
    void draw(sf::RenderWindow& window) override;
};
