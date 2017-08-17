#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <StdPlus/StdPlus.h>
#include "functions.h"

TEST(Simple, One)
{
    EXPECT_EQ(one(), 1);
}

TEST(read_vector_bool_from_bin_file, ExactSize)
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
        auto vec = read_vector_bool_from_bin_file(fileName, countBits);
        EXPECT_EQ(vec.size(), countBits);
    }
}

TEST(read_vector_bool_from_bin_file, LessSize)
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
        auto vec = read_vector_bool_from_bin_file(fileName, countBits);
        EXPECT_EQ(vec.size(), countBits);
    }
}

TEST(read_vector_bool_from_bin_file, MoreSize)
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
            auto vec = read_vector_bool_from_bin_file(fileName, countBits);
            AMSG("ERROR: Not exception in MoreSize request");
            throw;                
        }
        catch (std::logic_error & e)
        {
            AMSG(std::string("GOOD: catch: ") + e.what());
        }
    }
}

TEST(read_vector_bool_from_bin_file, NotExistFile)
{
    std::string fileName = "NotExistsFile.txt";

    try
    {
        auto vec = read_vector_bool_from_bin_file(fileName, 10);
        AMSG("ERROR: Not exception in MoreSize request");
        throw;
    }
    catch (std::logic_error & e)
    {
        AMSG(std::string("GOOD: catch: ") + e.what());
    }

}

TEST(DISABLED_readVectorBoolFromBinFile, RealFile)
{    
    std::string fileName1 = "Starter.xml";
    read_vector_bool_from_bin_file(fileName1, 48201*8);

    std::string fileName2 = "toeplitz_seed_16777282";
    read_vector_bool_from_bin_file(fileName2, 16777282);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();    
    
    std::cin.get();    

    return ret;
}
