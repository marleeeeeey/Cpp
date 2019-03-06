#include <unordered_map>
#include "TreeNode.hpp"
#include <iostream>
#include <cassert>

// sums by height: first - height, second - value for this height
std::unordered_map<int, int> sums;

int getSum(TreeNode<int> * parent, const int h, bool isRoot = true)
{
    if(parent == nullptr)
        return 0;

    if(h < 0)
        return 0;
    
    if(isRoot && sums.find(h) != sums.end()) // need to return this value in case
        return sums[h];                      // if it's root

    int sum = parent->value;

    if(parent->left)
        sum += getSum(parent->left, h - 1, false);

    if(parent->right)
        sum += getSum(parent->right, h - 1, false);

    if(isRoot)
        sums[h] = sum;
    
    return sum;
}

void main()
{
    TreeNode<int> * tree = generateTree({ 10, 5, 15, 3, 7, 12, 2 });
    std::cout << tree << "\n";

    assert(getSum(tree, 2) == 52);
    assert(getSum(tree, 3) == 54);
    assert(getSum(tree, 4) == 54);
    assert(getSum(tree, -1) == 0);
    assert(getSum(tree, 0) == 10);
    assert(getSum(tree, 1) == 30);

    std::cout << "sums:\n";
    for(auto p : sums)
    {
        std::cout << p.first << ". " << p.second << "\n";
    }

    for(auto & p : sums) // to check if sums works
        p.second++;

    assert(getSum(tree, -1) == 0);
    assert(getSum(tree, 0) == 11);
    assert(getSum(tree, 1) == 31);
    assert(getSum(tree, 2) == 53);
    assert(getSum(tree, 3) == 55);
    assert(getSum(tree, 4) == 55);

    std::cout << "sums:\n";
    for(auto p : sums)
    {
        std::cout << p.first << ". " << p.second << "\n";
    }

    std::cin.get();
}