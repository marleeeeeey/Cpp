#pragma once
#include "IObject.h"

enum class ObjectType
{
    Brick,
    Plate,
    Ball,
    Bonus,
    Wall,
};

class IObjectFactory
{
public:
    virtual ~IObjectFactory() = default;
    virtual std::shared_ptr<IObject> createObject(ObjectType objectType) = 0;
};
