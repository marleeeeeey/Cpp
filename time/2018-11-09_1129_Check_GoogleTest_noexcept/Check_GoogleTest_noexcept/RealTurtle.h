#pragma once
#include "TurtleIntf.h"

class RealTurtle : public TurtleIntf
{
public:
    RealTurtle();
    virtual ~RealTurtle();

    virtual void PenDown() override;
    virtual bool Forward(int distance) noexcept override;

    virtual int GetLastForwardValue() override;
private:
    int m_lastForwardValue = -1;
};

