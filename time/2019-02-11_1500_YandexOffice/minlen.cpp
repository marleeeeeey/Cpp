#include <vector>
#include <iostream>
#include <cassert>

int sum(const std::vector<int> & c, int f, int s)
{
    if(f >= c.size() || s >= c.size())
        throw std::logic_error("out of range");

    int ret = 0;

    for(int i = f; i <= s; i++)
    {
        ret += c[i];
    }

    return ret;
}

int getMinLen(const std::vector<int> & c, int k)
{
    int len = INT_MAX;
    
    if(c.empty())
        return len;
    
    int f = 0;
    int s = 0;
    int l = c.size() - 1;

    while(sum(c, f, s) < k)
    {
        s++;
        if(s >= l) // my mistake 1: should be >= instead ==
            return len;
    }

    while(true)
    {
        while(sum(c, f, s) >= k)
        {
            len = s - f + 1;
            if(len == 1) // my mistake 2: this statement should be before f++
                return 1;
            f++;    
        }

        while(sum(c, f, s) < k)
        {
            f++;
            s++;
            if(s == l)
                return len;
        }
    }
}

int main()
{
    assert(getMinLen({ 2, 3, 2, 8, 5, 4, 2, 4, 6, 7, 9, 2 }, 11) == 2);
    assert(getMinLen({ }, 11) == INT_MAX);
    assert(getMinLen({ 2, 3, 2, 1, 1 }, 11) == INT_MAX);
    assert(getMinLen({ 12 }, 11) == 1);
    assert(getMinLen({ 5 }, 11) == INT_MAX);
    std::cin.get();
}
