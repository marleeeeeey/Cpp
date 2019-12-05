#pragma once
#include "IObject.h"

class ILevelGenerator
{
public:
    virtual ~ILevelGenerator() = default;
    virtual std::vector<std::shared_ptr<IObject>> getLevelBricks() = 0;
    virtual void changeLevel() = 0;
    virtual void resetLevelProgress() = 0;
};
