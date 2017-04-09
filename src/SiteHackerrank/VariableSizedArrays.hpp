#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>


using namespace std;

typedef vector<int> Page;

Page readPage()
{
	int n;
	cin >> n;

	Page newPage;
	for (int i = 0; i < n; ++i)
	{
		int var;
		cin >> var;
		newPage.push_back(var);
	}

	return newPage;
}

int main() 
{
	int countInputLines;
	cin >> countInputLines;
	
	int countOutputLines;
	cin >> countOutputLines;

	cin.get();

	vector<Page> book;

	for (int i = 0; i < countInputLines; ++i)
	{
		book.push_back(readPage());
	}

	map<int, int> querys;
	for (int i = 0; i < countOutputLines; ++i)
	{
		int index;
		cin >> index;

		int var;
		cin >> var;

		querys[index] = var;
	}

	for (auto p : querys)
	{
		int lineIndex = p.first;
		int posIndex = p.second;

		int var = book.at(lineIndex).at(posIndex);
		cout << var << endl;
	}

	return 0;
}
