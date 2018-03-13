#include <gtest/gtest.h>

TEST(IsPrimeTest, Positive) 
{
    EXPECT_FALSE(false);
    EXPECT_FALSE(true);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}