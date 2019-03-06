#include <iostream>
#include <cassert>
#include "ListNode.hpp"
#include "TreeNode.hpp"

void mainList()
{
    auto list = generateList<int>({ 1, 2, 3, 4, 5, 8, 0, 2, 3 });
    assert(isEqual(list, generateList<int>({ 1, 2, 3, 4, 5, 8, 0, 2, 3 })));
    removeNode(&list, 8);
    assert(isEqual(list, generateList<int>({ 1, 2, 3, 4, 5, 0, 2, 3 })));
    insertNode(&list, 11);
    assert(isEqual(list, generateList<int>({ 11, 1, 2, 3, 4, 5, 0, 2, 3 })));
    auto node = searchNode(list, 0);
    assert(isEqual(node, generateList<int>({ 0, 2, 3 })));
    assert(isEqual(list, generateList<int>({ 11, 1, 2, 3, 4, 5, 0, 2, 3 })));
    auto list2 = generateList({ 2 });
    assert(isEqual(list2, generateList<int>({ 2 })));
    removeNode(&list2, 5);
    removeNode(&list2, 2);
    assert(isEqual(list2, generateList<int>({ })));
}

void main()
{
    TreeNode<int> * tree = generateTree({ 4, 5, 6, 7, 1, 2, 3 });
    std::cout << tree;
    std::cin.get();
}

