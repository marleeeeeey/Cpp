#include "StdPlus/StdPlus.h"

int solution(std::vector<int> & vars)
{
    int leftMax = vars.front();
    int rightMax = *std::max_element(vars.begin()+1, vars.end());
    int absDiffMax = abs(leftMax - rightMax);
    
    for (int i = 1; i < vars.size()-1; ++i)
    {
        int cur = vars[i];

        if (leftMax < cur)
            leftMax = cur;

        if (rightMax == cur)
            rightMax = *std::max_element(vars.begin() + i + 1, vars.end());

        int curAbsDiffMax = abs(leftMax - rightMax);

        if (curAbsDiffMax > absDiffMax)
            absDiffMax = curAbsDiffMax;
    }

    return absDiffMax;
}

int main()
{
    //std::vector<int> vars = { 1, 3, -3 };
    std::vector<int> vars = { 4, 3, 2, 5, 1, 1 };

    AVAR(solution(vars));

    APAUSE;
}