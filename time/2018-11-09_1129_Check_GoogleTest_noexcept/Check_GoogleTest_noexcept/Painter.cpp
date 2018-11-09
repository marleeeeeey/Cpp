#include "stdafx.h"
#include "Painter.h"

Painter::Painter(TurtleIntf* turtle)
    : m_turtle(turtle)
{
}

bool Painter::DrawCircle(int x, int y, int r)
{
    m_turtle->PenDown();
    m_turtle->PenDown();
    m_turtle->PenDown();
    m_turtle->PenDown();
    m_turtle->PenDown();
    m_turtle->PenDown();
    m_turtle->PenDown();
    m_turtle->PenDown();
    
    m_turtle->Forward(100);

    return true;
}

Painter::~Painter()
{
}
