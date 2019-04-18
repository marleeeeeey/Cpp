#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

// This example lead to UB
// because comparator does's consist to C++ named requirements: Compare
// https://en.cppreference.com/w/cpp/named_req/Compare

bool compareIt(const int& left, const int& right)
{
	std::cout << "left=" << left << ", ";
	std::cout << "right=" << right << ", ";

	static int val = 0;
	bool result = val % 2;
	val++;
	std::cout << "val=" << val << ", ";
	std::cout << "result=" << result << "\n";
	return result;
}

void useIt()
{
    std::vector<int> a{ 1, 1, 1, 1, 1, 1 };
    std::vector<int> b{ 2, 2, 2, 2, 2 };
    std::vector<int> c(a.size() + b.size());    

    std::merge(a.begin(), a.end(), b.begin(), b.end(), c.begin(), compareIt);

    // output a
    std::cout << "a : ";
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // output b
    std::cout << "b : ";
    std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // output c
    std::cout << "c : ";
    std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';    

	std::cin.get();
}