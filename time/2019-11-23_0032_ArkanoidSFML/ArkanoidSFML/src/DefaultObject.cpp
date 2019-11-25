#include "DefaultObject.h"
#include "HelperFunctions.h"

std::vector<Collision> getCollisions(std::shared_ptr<IObject> object,
    std::vector<std::shared_ptr<IObject>> secondaryObjects)
{
    std::vector<Collision> collisions;
    for(auto secondaryObject : secondaryObjects)
    {
        if(object == secondaryObject)
            continue;

        auto collision = hf::getIntersectRectShape(object->state().getCollisionRect(),
            secondaryObject->state().getCollisionRect());
        if(collision)
        {
            collisions.push_back({ secondaryObject, collision.value() });
        }
    }

    return collisions;
}


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

std::optional<std::vector<std::shared_ptr<IObject>>> DefaultObject::stealChildren()
{
    return {};
}

std::shared_ptr<IObjectFactory> DefaultObject::getObjectFactory()
{
    return m_objectFactory;
}

void DefaultObject::setOnBumpingCallBack(std::function<void(std::vector<Collision>& collisions)> cb)
{
    m_onBumpingCallback = cb;
}

void DefaultObject::checkBumping(std::vector<std::shared_ptr<IObject>> & objects)
{
    auto collisions = getCollisions(shared_from_this(), objects);
    if(m_onBumpingCallback)
        m_onBumpingCallback(collisions);
    onBumping(collisions);
}
