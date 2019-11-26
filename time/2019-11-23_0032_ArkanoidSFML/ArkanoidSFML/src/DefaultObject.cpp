#include "DefaultObject.h"
#include "HelperFunctions.h"

std::vector<Collision> getCollisions(std::shared_ptr<IObject> object,
                                     std::vector<std::shared_ptr<IObject>> secondaryObjects)
{
    std::vector<Collision> collisions;
    for (auto secondaryObject : secondaryObjects)
    {
        if (object == secondaryObject)
            continue;

        auto collision = hf::getIntersectRectShape(object->state().getCollisionRect(),
                                                   secondaryObject->state().getCollisionRect());
        if (collision)
        {
            collisions.emplace_back(secondaryObject, collision.value());
        }
    }

    return collisions;
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

void DefaultObject::setOnBumpingCallBack(
    std::function<void(std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)> cb)
{
    m_onBumpingCallback = cb;
}

void DefaultObject::checkBumping(std::vector<std::shared_ptr<IObject>>& objects)
{
    auto thisObject = shared_from_this();
    auto collisions = getCollisions(thisObject, objects);
    if (m_onBumpingCallback)
        m_onBumpingCallback(thisObject, collisions);
    onBumping(collisions);
    m_onBumpingCallback = {};
}
