#include "World.h"
#include "HelperFunctions.h"

std::vector<std::shared_ptr<IObject>> World::getAllObjects()
{
    std::vector<std::shared_ptr<IObject>> allObjects;
    auto mainObjects = getPrimaryObjects();
    auto noMainObjects = getSecondaryObjects();
    allObjects.insert(allObjects.end(), mainObjects.begin(), mainObjects.end());
    allObjects.insert(allObjects.end(), noMainObjects.begin(), noMainObjects.end());
    return allObjects;
}

std::vector<std::shared_ptr<IObject>> World::getPrimaryObjects()
{
    std::vector<std::shared_ptr<IObject>> objects;
    objects.insert(objects.end(), m_balls.begin(), m_balls.end());
    objects.insert(objects.end(), m_plates.begin(), m_plates.end());
    return objects;
}

std::vector<std::shared_ptr<IObject>> World::getSecondaryObjects()
{
    std::vector<std::shared_ptr<IObject>> objects;
    objects.insert(objects.end(), m_matrix.begin(), m_matrix.end());
    objects.insert(objects.end(), m_walls.begin(), m_walls.end());
    objects.insert(objects.end(), m_bonuses.begin(), m_bonuses.end());
    return objects;
}

bool World::isObjectOutOfBorder(std::shared_ptr<IObject> object)
{
    auto objectPos = object->state().getPos();
    if (objectPos.x < 0 || objectPos.y < 0 ||
        objectPos.x > m_worldSize.x ||
        objectPos.y > m_worldSize.y)
    {
        return true;
    }

    return false;
}

World::World(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize)
{
    m_worldSize = worldSize;
    m_objectFactory = objectFactory;
}

void World::generate()
{
    auto& of = m_objectFactory;
    sf::Vector2f screenCenter = {m_worldSize.x, m_worldSize.y};
    auto ball = of->createObject(ObjectType::Ball);
    ball->state().setPos(screenCenter);
    m_balls.push_back(ball);

    sf::Vector2f brickZoneSize = {m_worldSize.x * 0.8f, m_worldSize.y * 0.3f};
    sf::Vector2f brickZoneLeftTopPos = {m_worldSize.x * 0.1f, m_worldSize.y * 0.1f};
    sf::Vector2i resolutionInBricks = { 10, 5 };
    sf::Vector2f brickSize = { brickZoneSize.x / resolutionInBricks.x, brickZoneSize.y / resolutionInBricks.y };
    for (auto brickCol = 0; brickCol < resolutionInBricks.x; ++brickCol)
    {
        for (auto brickRow = 0; brickRow < resolutionInBricks.y; ++brickRow)
        {
            auto brick = of->createObject(ObjectType::Brick);
            sf::Vector2f brickPos = {
                brickSize.x / 2 + brickCol * brickSize.x + brickZoneLeftTopPos.x,
                brickSize.y / 2 + brickRow * brickSize.y + brickZoneLeftTopPos.y
            };
            brick->state().setPos(brickPos);
            brick->state().setSize(brickSize);
            m_matrix.push_back(brick);
        }
    }

    // TODO generate walls, plate, ...
}

bool World::isGameOver()
{
    return m_matrix.empty() || m_balls.empty();
}

void World::removeObjectsIfDestroyed(std::vector<std::shared_ptr<IObject>>& objects)
{
    auto removeIt = std::remove_if(objects.begin(), objects.end(),
                                   [](std::shared_ptr<IObject> object)
                                   {
                                       return object->state().getDestroyFlag();
                                   });

    objects.erase(removeIt, objects.end());
}

void World::removeAllDestroyedObjects()
{
    removeObjectsIfDestroyed(m_balls);
    removeObjectsIfDestroyed(m_plates);
    removeObjectsIfDestroyed(m_matrix);
    removeObjectsIfDestroyed(m_walls);
    removeObjectsIfDestroyed(m_bonuses);
}

std::vector<Collision> World::getCollisions(std::shared_ptr<IObject> object,
                                            std::vector<std::shared_ptr<IObject>> secondaryObjects)
{
    std::vector<Collision> collisions;
    for (auto secondaryObject : secondaryObjects)
    {
        auto collision = hf::getIntersectRectShape(object->state().getCollisionRect(),
                                                   secondaryObject->state().getCollisionRect());
        if (collision)
        {
            collisions.push_back({secondaryObject, collision.value()});
        }
    }

    return collisions;
}

void World::updateState(sf::Event event, sf::Time timeStep)
{
    auto allObjects = getAllObjects();
    for (auto object : allObjects)
    {
        object->calcState(event, timeStep);
        if (isObjectOutOfBorder(object))
        {
            object->state().setDestroyFlag(true);
        }
    }
    removeAllDestroyedObjects();

    for (auto primaryObject : getPrimaryObjects())
    {
        auto collisions = getCollisions(primaryObject, getSecondaryObjects());
        primaryObject->onBumping(collisions);
    }

    removeAllDestroyedObjects();
}

void World::draw(sf::RenderWindow& window)
{
    for (auto object : getAllObjects())
    {
        object->draw(window);
    }
}
