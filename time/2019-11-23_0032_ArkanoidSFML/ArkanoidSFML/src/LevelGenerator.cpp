#include "LevelGenerator.h"
#include "IDescructible.h"
#include "IBonusOwner.h"

void LevelGenerator::initLevels()
{
    std::vector<Level> levels
    {
        {
        "...31L1111L13...",
        "...3111111113...",
        "...3111111113...",
        "...3111111113...",
        "...311L11L113...",
        "...3111111113...",
        "...3111111113...",
        "...3111111113...",
        "...3111111113...",
        "...3111111113...",
        }
    };

    m_levels = levels;

}

LevelGenerator::LevelGenerator(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize)
{
    m_objectFactory = objectFactory;
    m_worldSize = worldSize;
    m_brickZoneSize = {m_worldSize.x * 0.8f, m_worldSize.y * 0.6f};
    m_brickZoneLeftTopPos = {m_worldSize.x * 0.1f, m_worldSize.y * 0.2f};
    m_resolutionInBricks = {15, 10};
    m_brickGap = 8;
    m_currentLevelNumber = 0;
    initLevels();
}

std::vector<std::shared_ptr<IObject>> LevelGenerator::getNextLevelBricks()
{
    auto levelNumber = m_currentLevelNumber % m_levels.size();
    auto currentLevel = m_levels.at(levelNumber);
    std::vector<std::shared_ptr<IObject>> bricks;
    sf::Vector2f brickSize = {
        m_brickZoneSize.x / m_resolutionInBricks.x,
        m_brickZoneSize.y / m_resolutionInBricks.y
    };
    for (auto brickCol = 0; brickCol < m_resolutionInBricks.x; ++brickCol)
    {
        for (auto brickRow = 0; brickRow < m_resolutionInBricks.y; ++brickRow)
        {
            char symbol = currentLevel[brickRow][brickCol];
            if(symbol == '.')
                continue;
            auto obj = m_objectFactory->createObject(ObjectType::Brick);
            sf::Vector2f brickPos = {
                brickSize.x / 2 + brickCol * brickSize.x + m_brickZoneLeftTopPos.x,
                brickSize.y / 2 + brickRow * brickSize.y + m_brickZoneLeftTopPos.y
            };
            obj->state().setPos(brickPos);
            obj->state().setSize({brickSize.x - m_brickGap, brickSize.y - m_brickGap});
            auto brick = std::dynamic_pointer_cast<IDescructible>(obj);
            auto bonus = std::dynamic_pointer_cast<IBonusOwner>(obj);
            if(std::isdigit(symbol))
            {
                int number = hf::charToInt(symbol);
                if(number == 0)
                    brick->setLives(999);
                else
                    brick->setLives(number);
                brick->setAppearance(number);
                bonus->setBonusType({});
            }
            else
            {
                brick->setLives(1);
                auto bonusType = getBonusTypeFromChar(symbol);
                brick->setAppearance(static_cast<int>(bonusType));
                bonus->setBonusType(bonusType);
            }
            bricks.push_back(obj);
        }
    }

    return bricks;
}

// ................
// ................
// ................
// ................
// ................
// ................
// ................
// ................
// ................
// ................
// ................



// ................
// .11111111111111.
// .11111111111111.
// .11111111111111.
// .11111111111111.
// .11111111111111.
// .11111111111111.
// .11111111111111.
// .11111111111111.
// .11111111111111.
// ................