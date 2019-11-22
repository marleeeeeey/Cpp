#include "ObjectFactory.h"

std::shared_ptr<IObject> ObjectFactory::createObject(ObjectType objectType)
{
    // TODO
    switch (objectType)
    {
    case ObjectType::Brick:

        break;
    case ObjectType::Plate: break;
    case ObjectType::Ball: break;
    case ObjectType::Bonus: break;
    case ObjectType::Wall: break;
    default: ;
    }
}
