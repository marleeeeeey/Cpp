#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "HelperFunctions.h"

TEST(HelperFunctions, RandomIntZero)
{
    EXPECT_EQ(hf::randomInt(0, 0), 0);
}
