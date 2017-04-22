
#include <iostream>
#include <vector>
#include <algorithm>

int main_1()
{
    int n;
    std::cin >> n;
    
    int k = 1;
    for ( ; k <= n; k++)
    {
        if (n % k != 0)
            break;
    }

    std::cout << k;
}

int main_2()
{
    std::vector<int> vars;

    for (int i = 0; i < 4; ++i)
    {
        int var;
        std::cin >> var;
        vars.push_back(var);
    }

    std::sort(vars.begin(), vars.end());

    int firstSum = vars.at(0) + vars.at(3);
    int lastSum = vars.at(1) + vars.at(2);

    if (firstSum == lastSum)
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
}

int main()
{

}