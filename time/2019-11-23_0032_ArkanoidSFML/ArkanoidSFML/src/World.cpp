#include "World.h"

World::World(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize)
{
    m_worldSize = worldSize;
    m_objectFactory = objectFactory;
}

void World::generate()
{
}

bool World::isGameOver()
{
}

void World::updateState(sf::Event event, sf::Time elapsedTime)
{
}

void World::draw(sf::RenderWindow& window)
{
}
