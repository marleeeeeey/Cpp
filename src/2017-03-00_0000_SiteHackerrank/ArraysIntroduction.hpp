#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() 
{
	int n = 0;
	cin >> n;
	std::vector<int> vars;
	for (int i = 0; i < n; ++i)
	{
		int var;
		cin >> var;
		vars.push_back(var);
	}

	for (int i = n-1; i >= 0; --i)
	{
		cout << vars.at(i) << " ";
	}

// 	for (auto & it = vars.begin(); it != vars.end(); it++)
// 	{
// 		cout << *it << " ";
// 	}

	return 0;
}
