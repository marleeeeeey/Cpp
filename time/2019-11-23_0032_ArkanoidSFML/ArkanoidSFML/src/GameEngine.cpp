#include "GameEngine.h"

GameEngine::GameEngine(std::shared_ptr<IWorld> world)
{
    m_world = world;
}

void GameEngine::setEvent(std::optional<sf::Event> event, sf::Time timeStep)
{
    m_world->updateState(event, timeStep);
    if (m_world->isGameOver())
    {
        m_world->generate();
    }
}

void GameEngine::draw(sf::RenderWindow& window)
{
    m_world->draw(window);
}
