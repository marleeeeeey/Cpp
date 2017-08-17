#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StdPlus/StdPlus.h>
#include "functions.h"

TEST(Simple, One)
{
    EXPECT_EQ(one(), 1);
}

TEST(charToVectorBool, ZeroChar)
{
    std::vector<bool> zeroVector(8, false);
    EXPECT_EQ(charToVectorBool((char)0), zeroVector);
}

TEST(charToVectorBool, ListBytes)
{
    std::map<char, std::vector<bool>> values =
    {
        {    0 ,{ 0, 0, 0, 0, 0, 0, 0, 0 } },
        {    1 ,{ 0, 0, 0, 0, 0, 0, 0, 1 } },
        {    2 ,{ 0, 0, 0, 0, 0, 0, 1, 0 } },
        {    3 ,{ 0, 0, 0, 0, 0, 0, 1, 1 } },
        {   32 ,{ 0, 0, 1, 0, 0, 0, 0, 0 } },
        {   64 ,{ 0, 1, 0, 0, 0, 0, 0, 0 } },
        {   96 ,{ 0, 1, 1, 0, 0, 0, 0, 0 } },
        { -128 ,{ 1, 0, 0, 0, 0, 0, 0, 0 } },
    };
    
    for (auto value : values)
    {
        EXPECT_EQ(charToVectorBool(value.first), value.second);
    }
}

TEST(readVectorBoolFromBinFile, ExactSize)
{
    std::string fileName = "karamba.txt";

    std::vector<std::string> strings = 
    { "karamba", "qwerqwer", "asdfasdfa", "", "qwerqwexcvz" };

    for (auto & str : strings)
    {
        int countBytes = str.size();
        std::ofstream ofs(fileName);
        ofs << str;
        ofs.close();

        size_t countBits = countBytes * 8;
        auto vec = readVectorBoolFromBinFile(fileName, countBits);
        EXPECT_EQ(vec.size(), countBits);
    }
}

TEST(readVectorBoolFromBinFile, LessSize)
{
    std::string fileName = "karamba.txt";

    std::vector<std::string> strings =
    { "karamba", "qwerqwer", "asdfasdfa", "qwerqwexcvz" };

    for (auto & str : strings)
    {
        int countBytes = str.size();
        std::ofstream ofs(fileName);
        ofs << str;
        ofs.close();

        size_t countBits = countBytes * 8 - 5;
        auto vec = readVectorBoolFromBinFile(fileName, countBits);
        EXPECT_EQ(vec.size(), countBits);
    }
}

TEST(readVectorBoolFromBinFile, MoreSize)
{
    std::string fileName = "karamba.txt";

    std::vector<std::string> strings =
    { "karamba", "qwerqwer", "asdfasdfa", "qwerqwexcvz", "" };

    for (auto & str : strings)
    {
        int countBytes = str.size();
        std::ofstream ofs(fileName);
        ofs << str;
        ofs.close();

        size_t countBits = countBytes * 8 + 5;
        try
        {
            auto vec = readVectorBoolFromBinFile(fileName, countBits);
            AMSG("ERROR: Not exception in MoreSize request");
            throw;                
        }
        catch (std::logic_error & e)
        {
            //AMSG(std::string("GOOD: catch: ") + e.what());
        }
    }
}

TEST(readVectorBoolFromBinFile, NotExistFile)
{
    std::string fileName = "NotExistsFile.txt";

    try
    {
        auto vec = readVectorBoolFromBinFile(fileName, 10);
        AMSG("ERROR: Not exception in MoreSize request");
        throw;
    }
    catch (std::logic_error & e)
    {
        //AMSG(std::string("GOOD: catch: ") + e.what());
    }

}

TEST(DISABLED_readVectorBoolFromBinFile, RealFile)
{    
    std::string fileName1 = "Starter.xml";
    readVectorBoolFromBinFile(fileName1, 48201*8);

    std::string fileName2 = "toeplitz_seed_16777282";
    readVectorBoolFromBinFile(fileName2, 16777282);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();    
    
    std::cin.get();    

    return ret;
}
