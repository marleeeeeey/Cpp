#include "World.h"
#include "HelperFunctions.h"
#include <iostream>

std::vector<std::shared_ptr<IObject>> World::getAllObjects()
{
    std::vector<std::shared_ptr<IObject>> allObjects;
    auto primaryObjects = getPrimaryObjects();
    auto secondaryObjects = getSecondaryObjects();
    allObjects.insert(allObjects.end(), primaryObjects.begin(), primaryObjects.end());
    allObjects.insert(allObjects.end(), secondaryObjects.begin(), secondaryObjects.end());
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
    objects.insert(objects.end(), m_bricks.begin(), m_bricks.end());
    objects.insert(objects.end(), m_walls.begin(), m_walls.end());
    objects.insert(objects.end(), m_bonuses.begin(), m_bonuses.end());
    objects.insert(objects.end(), m_plates.begin(), m_plates.end());
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
    std::cout << "World::generate()" << std::endl;
    removeAllObjects();

    auto& of = m_objectFactory;
    sf::Vector2f ballPos = {m_worldSize.x * 0.5f, m_worldSize.y * 0.9f};
    auto ball = of->createObject(ObjectType::Ball);
    ball->state().setPos(ballPos);
    ball->state().setSize({20, 20});
    m_balls.push_back(ball);

    sf::Vector2f brickZoneSize = {m_worldSize.x * 0.8f, m_worldSize.y * 0.3f};
    sf::Vector2f brickZoneLeftTopPos = {m_worldSize.x * 0.1f, m_worldSize.y * 0.1f};
    sf::Vector2i resolutionInBricks = {10, 5};
    float brickGap = 8;
    sf::Vector2f brickSize = {
        brickZoneSize.x / resolutionInBricks.x,
        brickZoneSize.y / resolutionInBricks.y
    };
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
            brick->state().setSize({brickSize.x - brickGap, brickSize.y - brickGap});
            m_bricks.push_back(brick);
        }
    }

    float wallKoefThinkness = 0.02;
    sf::Vector2f verticalWallSize = {m_worldSize.x * wallKoefThinkness, m_worldSize.y};
    auto leftWall = of->createObject(ObjectType::Wall);
    leftWall->state().setCollisionRect(verticalWallSize, {m_worldSize.x * wallKoefThinkness / 2, m_worldSize.y / 2});
    auto rightWall = of->createObject(ObjectType::Wall);
    rightWall->state().setCollisionRect(verticalWallSize,
                                        {m_worldSize.x * (1 - wallKoefThinkness / 2), m_worldSize.y / 2});
    sf::Vector2f horizontalWallSize = {m_worldSize.x, m_worldSize.y * wallKoefThinkness};
    auto topWall = of->createObject(ObjectType::Wall);
    topWall->state().setCollisionRect(horizontalWallSize, {m_worldSize.x / 2, m_worldSize.y * wallKoefThinkness / 2});

    m_walls.push_back(leftWall);
    m_walls.push_back(rightWall);
    m_walls.push_back(topWall);

    float plateKoefThinkness = 0.04;
    float plateKoefSize = 0.3;
    auto plate = of->createObject(ObjectType::Plate);
    plate->state().setSize({m_worldSize.x * plateKoefSize, m_worldSize.y * plateKoefThinkness});
    plate->state().setPos({m_worldSize.x / 2, m_worldSize.y * (1 - plateKoefThinkness)});
    m_plates.push_back(plate);

    std::cout << "count of objects is " << getAllObjects().size() << std::endl;
}

bool World::isGameOver()
{
    return m_bricks.empty() || m_balls.empty();
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
    removeObjectsIfDestroyed(m_bricks);
    removeObjectsIfDestroyed(m_walls);
    removeObjectsIfDestroyed(m_bonuses);
}

void World::removeAllObjects()
{
    m_balls.clear();
    m_plates.clear();
    m_bricks.clear();
    m_walls.clear();
    m_bonuses.clear();
}

std::vector<Collision> World::getCollisions(std::shared_ptr<IObject> object,
                                            std::vector<std::shared_ptr<IObject>> secondaryObjects)
{
    std::vector<Collision> collisions;
    for (auto secondaryObject : secondaryObjects)
    {
        if(object == secondaryObject)
            continue;

        auto collision = hf::getIntersectRectShape(object->state().getCollisionRect(),
                                                   secondaryObject->state().getCollisionRect());
        if (collision)
        {
            collisions.push_back({secondaryObject, collision.value()});
        }
    }

    return collisions;
}

void World::updateState(std::optional<sf::Event> event, sf::Time timeStep)
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

    auto secondaryObjects = getSecondaryObjects();

    for (auto primaryObject : getPrimaryObjects())
    {
        auto collisions = getCollisions(primaryObject, secondaryObjects);
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
