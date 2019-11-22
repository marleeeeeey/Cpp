#include "DefaultObject.h"

void DefaultObject::onBumping(std::vector<Collision>& collisions)
{
    // do nothing
}

void DefaultObject::calcState(sf::Event event, sf::Time elapsedTime)
{
    // do nothing
}

State DefaultObject::getState()
{
    return m_state;
}

void DefaultObject::setState(const State& state)
{
    m_state = state;
}
