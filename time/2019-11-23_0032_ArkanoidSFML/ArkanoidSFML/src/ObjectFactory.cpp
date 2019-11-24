#include "ObjectFactory.h"
#include "Brick.h"
#include "Ball.h"
#include "Wall.h"
#include "Plate.h"
#include "Bonus.h"

std::shared_ptr<IObject> ObjectFactory::createObject(ObjectType objectType)
{
    // TODO
    switch (objectType)
    {
    case ObjectType::Brick:
        return std::make_shared<Brick>(shared_from_this());
    case ObjectType::Plate:
        return std::make_shared<Plate>(shared_from_this());
    case ObjectType::Ball:
        return std::make_shared<Ball>(shared_from_this());
    case ObjectType::Bonus:
        return std::make_shared<Bonus>(shared_from_this());
    case ObjectType::Wall:
        return std::make_shared<Wall>(shared_from_this());
    default: ;
    }
}
