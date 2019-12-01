#pragma once
#include "MathVector.h"

class IDynamicObject
{
public:
    virtual ~IDynamicObject() = default;
    virtual void setSpeed(MathVector speed) = 0;
    virtual MathVector getSpeed() = 0;
};
