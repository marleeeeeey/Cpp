#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MathVector.h"

TEST(MathVector, DefaultConstructor)
{
    MathVector mathVector;
    EXPECT_EQ(sf::Vector2f( 0, 0 ), mathVector.getCoordinates());
}

TEST(MathVector, RightAngleDirections)
{
    MathVector mathVector(0, 100);
    EXPECT_EQ(sf::Vector2f(100, 0), mathVector.getCoordinates());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
