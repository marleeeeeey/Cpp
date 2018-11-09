#pragma once

class TurtleIntf 
{
public:
    virtual void PenDown() = 0;
    virtual bool Forward(int distance) noexcept = 0;
};