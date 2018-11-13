#include "stdafx.h"
#include "RealTurtle.h"
#include <stdexcept>
#include <iostream>


RealTurtle::RealTurtle()
{
}


RealTurtle::~RealTurtle()
{
}

void RealTurtle::PenDown()
{
    std::cout << "PenDown" << std::endl;
    return;
}

bool RealTurtle::Forward(int distance) noexcept
{
    m_lastForwardValue = distance;
    std::cout << "Forward" << distance << std::endl;
    return true;
}

int RealTurtle::GetLastForwardValue()
{
    return m_lastForwardValue;
}
