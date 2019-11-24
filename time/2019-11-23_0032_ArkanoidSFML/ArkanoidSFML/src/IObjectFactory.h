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

class IObjectFactory : public std::enable_shared_from_this<IObjectFactory>
{
public:
    virtual ~IObjectFactory() = default;
    virtual std::shared_ptr<IObject> createObject(ObjectType objectType) = 0;
};
