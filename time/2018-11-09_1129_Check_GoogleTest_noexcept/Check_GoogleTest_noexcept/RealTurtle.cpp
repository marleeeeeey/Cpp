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

void RealTurtle::PenUp() noexcept
{

}

void RealTurtle::PenDown()
{
    throw std::logic_error("The method or operation is not implemented.");
}

bool RealTurtle::Forward(int distance) noexcept
{
    std::cout << distance << std::endl;
    return 0;
}

void RealTurtle::Turn(int degrees)
{
    throw std::logic_error("The method or operation is not implemented.");
}

void RealTurtle::GoTo(int x, int y)
{
    throw std::logic_error("The method or operation is not implemented.");
}

int RealTurtle::GetX() const
{
    throw std::logic_error("The method or operation is not implemented.");
}

int RealTurtle::GetY() const
{
    throw std::logic_error("The method or operation is not implemented.");
}
