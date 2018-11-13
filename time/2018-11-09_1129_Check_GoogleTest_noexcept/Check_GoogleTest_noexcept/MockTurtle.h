#pragma once
#include "noexcept.h"
#include "gmock/gmock.h"  
#include "TurtleIntf.h"

class MockTurtle : public TurtleIntf 
{
public:
    MOCK_METHOD0(PenDown, void());
    MOCK_METHOD0(GetLastForwardValue, int());

    GMOCK_METHOD1_(, noexcept, , Forward, bool(int distance));

};
