#pragma once
#include "IObjectFactory.h"

class ObjectFactory : public IObjectFactory
{
public:
    std::shared_ptr<IObject> createObject(ObjectType objectType) override;
};
