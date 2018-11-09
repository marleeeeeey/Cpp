#pragma once

#include "gmock/gmock.h"  
#include "TurtleIntf.h"

class MockTurtle : public TurtleIntf 
{
public:
    MOCK_METHOD0(PenDown, void());
    MOCK_METHOD1(Forward, bool(int distance));
};
