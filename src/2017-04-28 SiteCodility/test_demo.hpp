#include "StdPlus/StdPlus.h"

int solution(std::vector<int> & vars)
{
    int leftSum = 0;
    int rightSum = std::accumulate(vars.begin(), vars.end(), 0);
    
    for (int i = 0; i < vars.size(); ++i)
    {
        rightSum -= vars[i];

        if (rightSum == leftSum)
            return i;

        leftSum += vars[i];
    }

    return -1;
}



int main()
{
    std::vector<int> vars = { -1, 3, -4, 5, 1, -6, 2, 1 };

    AVAR(solution(vars));

    APAUSE; 
}