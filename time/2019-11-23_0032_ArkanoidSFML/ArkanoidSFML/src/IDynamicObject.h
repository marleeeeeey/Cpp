#pragma once
#include "MathVector.h"

class IDynamicObject
{
public:
    virtual ~IDynamicObject() = default;
    virtual MathVector& speed() = 0;
};
