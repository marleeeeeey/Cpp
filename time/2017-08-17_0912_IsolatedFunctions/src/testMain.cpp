#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "functions.h"
#include <fstream>

TEST(Simple, One)
{
	EXPECT_EQ(one(), 1);
}

TEST(read_vector_bool_from_bin_file, exact_size)
{
	std::string file_name = "karamba.txt";

	std::vector<std::string> strings =
	{ "karamba", "qwerqwer", "asdfasdfa", "", "qwerqwexcvz" };

	for (auto & str : strings)
	{
		int count_bytes = str.size();
		std::ofstream ofs(file_name);
		ofs << str;
		ofs.close();

		size_t count_bits = count_bytes * 8;
		auto vec = read_vector_bool_from_bin_file(file_name, count_bits);
		EXPECT_EQ(vec.size(), count_bits);
	}
}

TEST(read_vector_bool_from_bin_file, less_size)
{
	std::string file_name = "karamba.txt";

	std::vector<std::string> strings =
	{ "karamba", "qwerqwer", "asdfasdfa", "qwerqwexcvz" };

	for (auto & str : strings)
	{
		int count_bytes = str.size();
		std::ofstream ofs(file_name);
		ofs << str;
		ofs.close();

		size_t count_bits = count_bytes * 8 - 5;
		auto vec = read_vector_bool_from_bin_file(file_name, count_bits);
		EXPECT_EQ(vec.size(), count_bits);
	}
}

TEST(read_vector_bool_from_bin_file, more_size)
{
	std::string file_name = "karamba.txt";

	std::vector<std::string> strings =
	{ "karamba", "qwerqwer", "asdfasdfa", "qwerqwexcvz", "" };

	for (auto & str : strings)
	{
		int count_bytes = str.size();
		std::ofstream ofs(file_name);
		ofs << str;
		ofs.close();

		size_t count_bits = count_bytes * 8 + 5;
		try
		{
			auto vec = read_vector_bool_from_bin_file(file_name, count_bits);
			ADD_FAILURE() << "Expected std::logic_error, but wrong exception cathed";
			throw;
		}
		catch (std::logic_error &)
		{
			SUCCEED();
		}
	}
}

TEST(read_vector_bool_from_bin_file, not_exists_file)
{
	std::string file_name = "NotExistsFile.txt";

	try
	{
		auto vec = read_vector_bool_from_bin_file(file_name, 10);
		ADD_FAILURE() << "Expected std::logic_error, but wrong exception cathed";
		throw;
	}
	catch (std::logic_error &)
	{
		SUCCEED();
	}
}

TEST(DISABLED_readVectorBoolFromBinFile, real_file)
{
	std::string file_name_1 = "Starter.xml";
	read_vector_bool_from_bin_file(file_name_1, 48201 * 8);

	std::string file_name_2 = "toeplitz_seed_16777282";
	read_vector_bool_from_bin_file(file_name_2, 16777282);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	int ret = RUN_ALL_TESTS();

	std::cin.get();

	return ret;
}