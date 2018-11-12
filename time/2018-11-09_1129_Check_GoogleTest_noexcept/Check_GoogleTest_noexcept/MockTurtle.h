#pragma once
#include "noexcept.h"
#include "gmock/gmock.h"  
#include "TurtleIntf.h"

class MockTurtle : public TurtleIntf 
{
public:
    MOCK_METHOD0(PenDown, void());

#if _MSC_VER < 1900
    MOCK_METHOD1(Forward, bool(int distance));
#else
    GMOCK_METHOD1_(, noexcept, , Forward, bool(int distance));
#endif

};
