#include <unordered_map>
#include "TreeNode.hpp"
#include <iostream>

// sums by depth
std::unordered_map<int, int> sums;

int getSum(TreeNode<int> * parent, const int h, const int d = 0)
{
    if(parent == nullptr)
        return 0;

    if(d > h)
        return 0;

    if(sums.find(h) != sums.end())
        return sums[h];
    
    int sum = parent->value;

    if(parent->left)
        sum += getSum(parent->left, h, d + 1);

    if(parent->right)
        sum += getSum(parent->right, h, d + 1);

    sums[h - d] = sum;

    return sum;
}

void main()
{
    // TODO add asserts
    TreeNode<int> * tree = generateTree({ 10, 5, 15, 3, 7, 12, 2 });
    std::cout << tree << "\n";
    std::cout << "sum(0)=" << getSum(tree, 0) << "\n";
    std::cout << "sum(1)=" << getSum(tree, 1) << "\n";
    std::cout << "sum(2)=" << getSum(tree, 2) << "\n";
    std::cout << "sum(3)=" << getSum(tree, 3) << "\n";
    std::cout << "sum(4)=" << getSum(tree, 4) << "\n";
    std::cout << "sum(5)=" << getSum(tree, 5) << "\n";
    std::cout << "sum(5)=" << getSum(tree, 5) << "\n";
    std::cin.get();
}