#pragma once
#include "Turtle.h"
class RealTurtle : public Turtle
{
public:
    RealTurtle();
    virtual ~RealTurtle();



    virtual void PenUp() noexcept override;


    virtual void PenDown() override;


    virtual bool Forward(int distance) noexcept override;


    virtual void Turn(int degrees) override;


    virtual void GoTo(int x, int y) override;


    virtual int GetX() const override;


    virtual int GetY() const override;

};

