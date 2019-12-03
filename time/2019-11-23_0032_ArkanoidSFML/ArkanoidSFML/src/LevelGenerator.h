#pragma once
#include "ILevelGenerator.h"
#include "IObjectFactory.h"
#include "gtest/gtest_prod.h"

using Level = std::vector<std::string>;

class LevelGenerator : public ILevelGenerator
{
    FRIEND_TEST(LevelGenerator, LevelLinesHaveSameSize);

    std::shared_ptr<IObjectFactory> m_objectFactory;
    sf::Vector2f m_worldSize;
    sf::Vector2f m_brickZoneSize;
    sf::Vector2f m_brickZoneLeftTopPos;
    float m_brickGap;
    std::vector<Level> m_levels;
    unsigned m_currentLevelNumber;

    std::vector<Level> getSymbolLevels();

public:
    LevelGenerator(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize);
    void changeLevel();
    std::vector<std::shared_ptr<IObject>> getLevelBricks() override;
};
