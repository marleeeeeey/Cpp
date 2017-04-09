#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


int main()
{
	std::map<int, string> numberDict =
	{
		{ 0, "zero" },
		{ 1, "one" },
		{ 2, "two" },
		{ 3, "three" },
		{ 4, "four" },
		{ 5, "five" },
		{ 6, "six" },
		{ 7, "seven" },
		{ 8, "eight" },
		{ 9, "nine" },
	};

	int n;
	cin >> n;

	if (n <= 0)
	{
		// do nothing
	}
	else if (n > 9)
	{
		cout << "Greater than 9";
	}
	else
	{
		cout << numberDict.at(n);
	}

	return 0;
}
