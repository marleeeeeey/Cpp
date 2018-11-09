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
    std::cout << "Forward" << distance << std::endl;
    return false;
}
