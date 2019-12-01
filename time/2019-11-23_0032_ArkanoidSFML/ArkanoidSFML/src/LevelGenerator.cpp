#include "LevelGenerator.h"
#include "IDescructible.h"
#include "IBonusOwner.h"

LevelGenerator::LevelGenerator(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize)
{
    m_objectFactory = objectFactory;
    m_worldSize = worldSize;
    m_brickZoneSize = {m_worldSize.x * 0.8f, m_worldSize.y * 0.6f};
    m_brickZoneLeftTopPos = {m_worldSize.x * 0.1f, m_worldSize.y * 0.2f};
    m_resolutionInBricks = {15, 10};
    m_brickGap = 8;
}

std::vector<std::shared_ptr<IObject>> LevelGenerator::getNextLevelBricks()
{
    std::vector<std::shared_ptr<IObject>> bricks;
    sf::Vector2f brickSize = {
        m_brickZoneSize.x / m_resolutionInBricks.x,
        m_brickZoneSize.y / m_resolutionInBricks.y
    };
    for (auto brickCol = 0; brickCol < m_resolutionInBricks.x; ++brickCol)
    {
        for (auto brickRow = 0; brickRow < m_resolutionInBricks.y; ++brickRow)
        {
            auto obj = m_objectFactory->createObject(ObjectType::Brick);
            sf::Vector2f brickPos = {
                brickSize.x / 2 + brickCol * brickSize.x + m_brickZoneLeftTopPos.x,
                brickSize.y / 2 + brickRow * brickSize.y + m_brickZoneLeftTopPos.y
            };
            obj->state().setPos(brickPos);
            obj->state().setSize({brickSize.x - m_brickGap, brickSize.y - m_brickGap});
            auto brick = std::dynamic_pointer_cast<IDescructible>(obj);
            brick->setAppearance(brickRow);
            auto bonus = std::dynamic_pointer_cast<IBonusOwner>(obj);
            bonus->setBonusType(getBonusTypeFromInt(brickCol));
            bricks.push_back(obj);
        }
    }

    return bricks;
}
