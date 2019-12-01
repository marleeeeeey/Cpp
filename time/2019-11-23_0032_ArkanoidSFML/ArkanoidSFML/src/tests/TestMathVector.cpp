#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MathVector.h"
#include "HelperFunctions.h"

void checkMathVector(MathVector mv, sf::Vector2f expectedResult)
{
    auto mvCoodinate = mv.getCoordinates();
    EXPECT_TRUE(hf::isEqual(expectedResult.x, mvCoodinate.x));
    EXPECT_TRUE(hf::isEqual(expectedResult.y, mvCoodinate.y));
}

TEST(MathVector, SimpleDirections)
{
    checkMathVector(MathVector(0, 0), { 0, 0 });
    checkMathVector(MathVector(0, 100), { 100, 0 });
    checkMathVector(MathVector(180, 100), { -100, 0 });
    checkMathVector(MathVector(-90, 100), { 0, -100 });
    checkMathVector(MathVector(90, 100), { 0, 100 });
}

TEST(MathVector, Flip_0_90)
{
    MathVector mv{ 0, 0 };
    mv.reflectFromHorizontal();
    checkMathVector(mv, { 0,0 });
    mv.reflectFromVertical();
    checkMathVector(mv, { 0,0 });

    mv.setAngle(0);
    mv.setSize(100);
    checkMathVector(mv, { 100, 0 });
    mv.reflectFromVertical();
    checkMathVector(mv, { -100, 0 });
    mv.reflectFromVertical();
    checkMathVector(mv, { 100, 0 });
    mv.reflectFromHorizontal();
    checkMathVector(mv, { 100, 0 });

    mv.setAngle(90);
    mv.setSize(100);
    checkMathVector(mv, { 0,100 });
    mv.reflectFromHorizontal();
    checkMathVector(mv, { 0, -100 });
    mv.reflectFromHorizontal();
    checkMathVector(mv, { 0,100 });
    mv.reflectFromVertical();
    checkMathVector(mv, { 0,100 });
}

TEST(MathVector, Flip_30)
{
    MathVector mv{ 30, 100 };
    EXPECT_TRUE(hf::isEqual(30.f, mv.getAngle()));
    mv.reflectFromVertical();
    EXPECT_TRUE(hf::isEqual(150.f, mv.getAngle()));
    mv.reflectFromVertical();
    EXPECT_TRUE(hf::isEqual(30.f, mv.getAngle()));
    mv.reflectFromHorizontal();
    EXPECT_TRUE(hf::isEqual(-30.f, mv.getAngle()));
}