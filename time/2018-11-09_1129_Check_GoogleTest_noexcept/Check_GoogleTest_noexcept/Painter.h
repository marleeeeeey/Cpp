#pragma once
#include "TurtleIntf.h"

class Painter
{
public:
    Painter(TurtleIntf* turtle);
    ~Painter();
    bool DrawCircle(int x, int y, int r);
private:
    TurtleIntf* m_turtle;
};

