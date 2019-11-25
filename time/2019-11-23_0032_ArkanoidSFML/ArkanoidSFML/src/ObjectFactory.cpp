#include "ObjectFactory.h"
#include "Brick.h"
#include "Ball.h"
#include "Wall.h"
#include "Plate.h"
#include "Bonus.h"

std::shared_ptr<IObject> ObjectFactory::createObject(ObjectType objectType)
{
    switch (objectType)
    {
    case ObjectType::Brick:
        return std::make_shared<Brick>();
    case ObjectType::Plate:
        return std::make_shared<Plate>();
    case ObjectType::Ball:
        return std::make_shared<Ball>();
    case ObjectType::Bonus:
        return std::make_shared<Bonus>();
    case ObjectType::Wall:
        return std::make_shared<Wall>();
    default: ;
    }
}
