#include "LevelGenerator.h"
#include "IDestructible.h"
#include "IBonusOwner.h"
#include "HelperFunctions.h"
#include <iostream>

std::vector<Level> LevelGenerator::getSymbolLevels()
{
    std::vector<Level> newLevels
    {
        {
            "...........",
            "...........",
            "...........",
            "33333333333",
            "11R11311R11",
            "11111311111",
            "11111311111",
            "111L131L111",
            "11111311111",
            "M111131111M",
            "11111311111",
            "33333333333",
            "...........",
            "...........",
            "...........",
            "...........",
        },
        {
            "...........",
            "...........",
            "...........",
            "...11111...",
            "..1111111..",
            "..1111111..",
            ".1111R1111.",
            ".1111.1111.",
            ".111F.F111.",
            "1111...1111",
            "11M1...1M11",
            "1111...1111",
            "111.....111",
            "111.....111",
            "11L.....L11",
            "2222...2222",
        },
        {
            "...........",
            "...........",
            "...........",
            "...11M11...",
            "...00000...",
            "...........",
            "..1111111..",
            "..0000000..",
            "...........",
            ".L1111111L.",
            ".000000000.",
            "...........",
            "..111R111..",
            "..0000000..",
            "...........",
            "...........",
        },
        {
            "................",
            ".0GGGMMMMMMGGG0.",
            ".00000000000000.",
            ".M.1111111111.M.",
            ".M.1111111111.M.",
            ".M.1111111111.M.",
            ".M.0000000000.M.",
            ".M............M.",
            "11111G1111G11111",
            "................",
            "................",
            "................",
        },
        {
            "................",
            "3333333333333333",
            "11....D11D....11",
            "S1....D11D....1S",
            "S1.FF.D11D.FF.1S",
            "S1....D11D....1S",
            "S1....D11D....1S",
            "S1....D11D....1S",
            "11....D11D....11",
            "000RRR0000RRR000",
            "................",
            "................",
        },
        {
            "................",
            "...31M1111M13...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
            "...311M11M113...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
            "...3111111113...",
        },
        {
            "........MM........",
            ".0022200000022200.",
            ".011R11111111R110.",
            ".0111111111111110.",
            ".0111111111111110.",
            ".0111111FF1111110.",
            ".0111111111111110.",
            ".0000000000000000.",
        },
    };

    m_currentLevelNumber += hf::randomInt(0, newLevels.size() - 1);
    return newLevels;
}

LevelGenerator::LevelGenerator(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize)
{
    m_objectFactory = objectFactory;
    m_worldSize = worldSize;
    float wide = 0.95;
    m_brickZoneSize = {m_worldSize.x * wide, m_worldSize.y * 0.6f};
    m_brickZoneLeftTopPos = {m_worldSize.x * (1 - wide) / 2, m_worldSize.y * 0.1f};
    m_brickGap = 5;
    m_currentLevelNumber = 0;
    m_levels = getSymbolLevels();
}

void LevelGenerator::changeLevel()
{
    m_currentLevelNumber += hf::randomInt(0, m_levels.size() - 1);
}

std::vector<std::shared_ptr<IObject>> LevelGenerator::getLevelBricks()
{
    auto levelNumber = m_currentLevelNumber % m_levels.size();
    auto currentLevel = m_levels.at(levelNumber);
    sf::Vector2i resolutionInBricks;
    resolutionInBricks.x = currentLevel.front().size();
    resolutionInBricks.y = currentLevel.size();
    std::vector<std::shared_ptr<IObject>> bricks;
    sf::Vector2f brickSize = {
        m_brickZoneSize.x / resolutionInBricks.x,
        m_brickZoneSize.y / resolutionInBricks.y
    };
    for (auto brickCol = 0; brickCol < resolutionInBricks.x; ++brickCol)
    {
        for (auto brickRow = 0; brickRow < resolutionInBricks.y; ++brickRow)
        {
            char symbol = currentLevel[brickRow][brickCol];
            if (symbol == '.')
                continue;
            auto obj = m_objectFactory->createObject(ObjectType::Brick);
            sf::Vector2f brickPos = {
                brickSize.x / 2 + brickCol * brickSize.x + m_brickZoneLeftTopPos.x,
                brickSize.y / 2 + brickRow * brickSize.y + m_brickZoneLeftTopPos.y
            };
            obj->state().setPos(brickPos);
            obj->state().setSize({brickSize.x - m_brickGap, brickSize.y - m_brickGap});
            auto brick = std::dynamic_pointer_cast<IDestructible>(obj);
            auto bonus = std::dynamic_pointer_cast<IBonusOwner>(obj);
            if (std::isdigit(symbol))
            {
                int number = hf::charToInt(symbol);
                if (number == 0)
                    brick->lives() = {};
                else
                    brick->lives() = number;
                bonus->bonusType() = {};
            }
            else
            {
                brick->lives() = 1;
                bonus->bonusType() = getBonusTypeFromChar(symbol);
            }
            bricks.push_back(obj);
        }
    }

    return bricks;
}

void LevelGenerator::resetLevelProgress()
{
    m_currentLevelNumber = 0;
}
