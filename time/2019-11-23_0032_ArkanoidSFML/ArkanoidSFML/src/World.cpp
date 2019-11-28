#include "World.h"
#include "HelperFunctions.h"
#include <iostream>
#include <sstream>
#include "IBonusOwner.h"

std::vector<std::shared_ptr<IObject>> World::getAllObjects()
{
    std::vector<std::shared_ptr<IObject>> objects;
    objects.insert(objects.end(), m_balls.begin(), m_balls.end());
    objects.insert(objects.end(), m_plates.begin(), m_plates.end());
    objects.insert(objects.end(), m_bricks.begin(), m_bricks.end());
    objects.insert(objects.end(), m_walls.begin(), m_walls.end());
    objects.insert(objects.end(), m_bonuses.begin(), m_bonuses.end());
    return objects;
}

bool World::isObjectOutOfBorder(std::shared_ptr<IObject> object)
{
    auto objectPos = object->state().getPos();
    if (objectPos.x < 0 || objectPos.y < 0 ||
        objectPos.x > m_windowSize.x ||
        objectPos.y > m_windowSize.y)
    {
        return true;
    }

    return false;
}

World::World(std::shared_ptr<IObjectFactory> objectFactory, std::shared_ptr<ILevelGenerator> levelGenerator, sf::Vector2f windowSize)
{
    m_objectFactory = objectFactory;
    m_levelGenerator = levelGenerator;
    m_windowSize = windowSize;
    m_font = hf::getDefaultFont();
    m_isGameOver = true;
    m_scopes = 0;
}

void World::initCollisionProcessors()
{
    m_collisionBuckets.push_back({m_balls, m_walls, {}});
    m_collisionBuckets.push_back({m_balls, m_plates, {}});
    m_collisionBuckets.emplace_back(
        m_balls, m_bricks, [&](std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)
        {
            if (!collisions.empty())
            {
                auto brick = std::dynamic_pointer_cast<IBonusOwner>(collisions.front().getObject());
                auto object = m_objectFactory->createObject(ObjectType::Bonus);
                object->state().setSize({5, 5});
                object->state().setPos(thisObject->state().getPos());
                auto bonus = std::dynamic_pointer_cast<IBonusOwner>(object);
                bonus->setBonusType(brick->getBonusType());
                m_bonuses.push_back(object);
            }
        }
    );
    m_collisionBuckets.push_back({m_plates, m_walls, {}});
    m_collisionBuckets.emplace_back(
        m_plates, m_bonuses, [&](std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions)
        {
            for (auto& collision : collisions)
            {
                auto obj = collision.getObject();
                obj->state().setDestroyFlag(true);
                m_scopes++;
            }
        }
    );
}

void World::initPlates()
{
    float plateKoefThinkness = 0.04;
    float plateKoefSize = 0.2;
    auto plate = m_objectFactory->createObject(ObjectType::Plate);
    plate->state().setSize({m_windowSize.x * plateKoefSize, m_windowSize.y * plateKoefThinkness});
    plate->state().setPos({m_windowSize.x / 2, m_windowSize.y * (1 - plateKoefThinkness)});
    plate->setOnBumpingCallBack([&](auto, std::vector<Collision>& collisions)
    {
        m_scopes += collisions.size();
    });
    m_plates.push_back(plate);
}

void World::initWalls()
{
    float wallKoefThinkness = 0.02;
    float wallTopOffset = 0.05;
    sf::Vector2f verticalWallSize = {m_windowSize.x * wallKoefThinkness, m_windowSize.y * (1 - wallTopOffset)};
    auto leftWall = m_objectFactory->createObject(ObjectType::Wall);
    leftWall->state().setCollisionRect(verticalWallSize,
                                       {m_windowSize.x * wallKoefThinkness / 2, m_windowSize.y * (0.5f + wallTopOffset)});
    auto rightWall = m_objectFactory->createObject(ObjectType::Wall);
    rightWall->state().setCollisionRect(verticalWallSize,
                                        {
                                            m_windowSize.x * (1 - wallKoefThinkness / 2),
                                            m_windowSize.y * (0.5f + wallTopOffset)
                                        });
    sf::Vector2f horizontalWallSize = {m_windowSize.x, m_windowSize.y * wallKoefThinkness};
    auto topWall = m_objectFactory->createObject(ObjectType::Wall);
    topWall->state().setCollisionRect(horizontalWallSize,
                                      {m_windowSize.x / 2, m_windowSize.y * (wallKoefThinkness / 2 + wallTopOffset)});
    m_walls.push_back(leftWall);
    m_walls.push_back(rightWall);
    m_walls.push_back(topWall);
}

void World::initBricks()
{
    m_bricks = m_levelGenerator->getNextLevelBricks();
}

void World::initBalls()
{
    sf::Vector2f ballPos = {m_windowSize.x * 0.5f, m_windowSize.y * 0.9f};
    auto ball = m_objectFactory->createObject(ObjectType::Ball);
    ball->state().setPos(ballPos);
    ball->state().setSize({20, 20});
    m_balls.push_back(ball);
}

void World::generate()
{
    m_isGameOver = false;
    removeAllObjects();
    m_collisionBuckets.clear();

    initBalls();
    initBricks();
    initWalls();
    initPlates();
    initCollisionProcessors();
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

void World::updateGameOverStatus()
{
    auto isAllBallsOutOfBorder = std::none_of(m_balls.begin(), m_balls.end(), [&](auto ball)
    {
        return !isObjectOutOfBorder(ball);
    });

    if (isAllBallsOutOfBorder && !m_bricks.empty())
    {
        m_scopes = 0;
        m_isGameOver = true;
    }
    else if (m_bricks.empty())
    {
        std::for_each(m_balls.begin(), m_balls.end(), [](std::shared_ptr<IObject> ballObject)
        {
            ballObject->state().setDestroyFlag(true);
        });

        if (m_bonuses.empty())
            m_isGameOver = true;
    }
}

void World::updateState(std::optional<sf::Event> event, sf::Time timeStep)
{
    if (m_isGameOver)
    {
        generate();
    }

    for (auto& collisionProcessor : m_collisionBuckets)
    {
        collisionProcessor.process();
    }
    removeAllDestroyedObjects();

    for (auto object : getAllObjects())
    {
        object->calcState(event, timeStep);
        if (isObjectOutOfBorder(object))
        {
            object->state().setDestroyFlag(true);
        }
    }
    removeAllDestroyedObjects();

    updateGameOverStatus();
}

void World::draw(sf::RenderWindow& window)
{
    for (auto object : getAllObjects())
    {
        object->draw(window);
    }

    sf::Text text;
    text.setFont(m_font);
    text.setScale(0.7, 0.7);
    std::ostringstream ss;
    ss << "Scopes: " << m_scopes << std::endl;
    text.setString(ss.str());
    window.draw(text);
}
