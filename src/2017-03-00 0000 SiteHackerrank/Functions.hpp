#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


int max_of_four(int a, int b, int c, int d)
{
	std::vector<int> vars{ a, b, c, d };
	std::sort(vars.begin(), vars.end());
	return vars.back();
}


int main() {
	int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	int ans = max_of_four(a, b, c, d);
	printf("%d", ans);

	return 0;
}

