#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "MathVector.h"

template<typename T>
bool isEqual(T lhs, T rhs)
{
    return fabs(lhs - rhs) < std::numeric_limits<T>::epsilon() * 100;
}

void checkMathVector(MathVector mv, sf::Vector2f expectedResult)
{
    EXPECT_TRUE(isEqual(expectedResult.x, mv.getCoordinates().x));
    EXPECT_TRUE(isEqual(expectedResult.y, mv.getCoordinates().y));
}

TEST(MathVector, AllDirections)
{
    checkMathVector(MathVector(0, 0), { 0, 0 });
    checkMathVector(MathVector(0, 100), { 100, 0 });
    checkMathVector(MathVector(180, 100), { -100, 0 });
    checkMathVector(MathVector(-90, 100), { 0, -100 });
    checkMathVector(MathVector(90, 100), { 0, 100 });
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    RUN_ALL_TESTS();
    std::cout << "Press any key to quit";
    std::cin.get();
}
