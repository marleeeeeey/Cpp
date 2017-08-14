#include <my_math/my_math.h>
#include <gtest/gtest.h>

TEST(MyMath, One) 
{
    EXPECT_EQ(my_math::one(), 1);
}

TEST(MyMath, Two) 
{
    EXPECT_EQ(my_math::two(), 2);
}

TEST(MyMath, Sum) 
{
    EXPECT_EQ(my_math::sum(1, 4), 5);
}


TEST(MyMath, WrongTest)
{
    EXPECT_EQ(my_math::sum(1, 4), 10);
}

