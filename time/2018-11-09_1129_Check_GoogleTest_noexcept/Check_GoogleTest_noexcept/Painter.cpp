#include "stdafx.h"
#include "Painter.h"
#include <iostream>

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
    
    bool result = m_turtle->Forward(333);
    if (result == false)
        throw std::exception();
    int valueReturnSomething = m_turtle->GetLastForwardValue();
    std::cout << "valueReturnSomething=" << valueReturnSomething << std::endl;


    return true;
}

Painter::~Painter()
{
}
