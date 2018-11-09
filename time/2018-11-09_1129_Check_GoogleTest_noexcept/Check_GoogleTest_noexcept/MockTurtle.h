#pragma once

#include "gmock/gmock.h"  
#include "TurtleIntf.h"

class MockTurtle : public TurtleIntf 
{
public:
    MOCK_METHOD0(PenDown, void());
    GMOCK_METHOD1_(, noexcept, , Forward, bool(int distance));
};
