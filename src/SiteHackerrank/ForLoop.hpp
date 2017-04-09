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

void printNumber(int n)
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

	cout << numberDict.at(n) << endl;
}

int main()
{
	int startIndex = 0;
	int endIndex   = 0;
	cin >> startIndex;
	cin >> endIndex;

	for (int i = startIndex; i <= endIndex; ++i)
	{
		if (i >= 1 && i <= 9)
		{
			printNumber(i);
		}
		else if (i > 9)
		{
			if (i % 2 == 0)
				cout << "even" << endl;
			else
				cout << "odd" << endl;
		}
	}

	return 0;
}
