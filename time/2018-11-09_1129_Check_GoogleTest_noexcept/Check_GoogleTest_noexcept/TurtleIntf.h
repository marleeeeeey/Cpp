#pragma once
#include "noexcept.h"

class TurtleIntf 
{
public:
    virtual void PenDown() = 0;
    virtual int GetLastForwardValue() = 0;
    virtual bool Forward(int distance) noexcept = 0;
};