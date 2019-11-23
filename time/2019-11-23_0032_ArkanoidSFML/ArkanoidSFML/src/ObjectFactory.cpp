#include "ObjectFactory.h"
#include "Brick.h"
#include "Ball.h"

std::shared_ptr<IObject> ObjectFactory::createObject(ObjectType objectType)
{
    // TODO
    switch (objectType)
    {
    case ObjectType::Brick:
        return std::make_shared<Brick>();
    case ObjectType::Plate: break;
    case ObjectType::Ball:
        return std::make_shared<Ball>();
    case ObjectType::Bonus: break;
    case ObjectType::Wall: break;
    default: ;
    }
}
