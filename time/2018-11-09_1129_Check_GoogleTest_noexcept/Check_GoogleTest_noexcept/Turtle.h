#pragma once

class Turtle 
{
public:
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual bool Forward(int distance) noexcept = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};