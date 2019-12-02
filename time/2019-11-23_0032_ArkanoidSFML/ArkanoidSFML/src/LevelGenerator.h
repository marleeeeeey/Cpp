#pragma once
#include "ILevelGenerator.h"
#include "IObjectFactory.h"

using Level = std::vector<std::string>;

class LevelGenerator : public ILevelGenerator
{
    std::shared_ptr<IObjectFactory> m_objectFactory;
    sf::Vector2f m_worldSize;
    sf::Vector2f m_brickZoneSize;
    sf::Vector2f m_brickZoneLeftTopPos;
    sf::Vector2i m_resolutionInBricks;
    float m_brickGap;
    std::vector<Level> m_levels;
    unsigned m_currentLevelNumber;

    void initLevels();

public:
    LevelGenerator(std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize);
    std::vector<std::shared_ptr<IObject>> getNextLevelBricks() override;
};
