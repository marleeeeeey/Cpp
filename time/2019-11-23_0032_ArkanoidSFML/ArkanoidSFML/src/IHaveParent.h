#pragma once
#include "IObject.h"

class IHaveParent
{
public:
    virtual ~IHaveParent() = default;
    virtual void setParent(std::shared_ptr<IObject> parent) = 0;
    virtual void removeParent() = 0;
};
