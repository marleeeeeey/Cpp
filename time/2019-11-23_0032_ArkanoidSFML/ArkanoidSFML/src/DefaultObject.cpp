#include "DefaultObject.h"

DefaultObject::DefaultObject(std::shared_ptr<IObjectFactory> objectFactory)
{
    m_objectFactory = objectFactory;
}

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

std::optional<std::vector<IObject>> DefaultObject::getChildren()
{
    return {};
}

std::shared_ptr<IObjectFactory> DefaultObject::getObjectFactory()
{
    return m_objectFactory;
}
