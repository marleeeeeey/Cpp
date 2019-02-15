#include <map>
#include <set>
#include <cassert>

template <typename T>
std::set<T> removeSecond(std::set<T> & c)
{
    auto elem = c.begin();
    while(elem != c.end())
    {
        elem++;
        if(elem == c.end())
            break;
        elem = c.erase(elem);
    }

    return c;
}

template <typename T>
std::set<T> removeSecond(std::initializer_list<T> il)
{
    std::set<T> c = il;
    return removeSecond(c);
}


int main()
{
    assert(removeSecond<int>({ 1, 2, 3, 4, 5, 6, 7 }) == std::set<int> ({ 1, 3, 5, 7 }));
    assert(removeSecond<int>({ 1 }) == std::set<int>({ 1 }));
    assert(removeSecond<int>({ }) == std::set<int>({ }));
    assert(removeSecond<int>({ 1, 2, 3, 4, 5, 6, 7, 8 }) == std::set<int>({ 1, 3, 5, 7 }));
}