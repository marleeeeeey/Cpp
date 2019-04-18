#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>

auto get_lambda()
{
	int v = false;
	
	// in case v pass by value
	// mutable used to make this variable non const.
	auto lambdaFunc = [v](auto && b) mutable
	{
		b = v;
		v = !v;
	};

	return lambdaFunc;
}

int main()
{
	auto labmda = get_lambda();

	std::vector<int> vec;
	vec.resize(10);

	std::for_each(vec.begin(), vec.end(), labmda);

	std::cout << "vec : ";
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << '\n';
	std::cin.get();
}