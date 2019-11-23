#include "DefaultObject.h"

void DefaultObject::onBumping(std::vector<Collision>& collisions)
{
    // do nothing
}

void DefaultObject::calcState(std::optional<sf::Event> event, sf::Time elapsedTime)
{
    // do nothing
}

void DefaultObject::draw(sf::RenderWindow& window)
{
}

State& DefaultObject::state()
{
    return m_state;
}
