#pragma once
#include "Turtle.h"

class Painter
{
public:
    Painter(Turtle* turtle);
    bool DrawCircle(int x, int y, int r);
    ~Painter();

    Turtle* m_turtle;
};

