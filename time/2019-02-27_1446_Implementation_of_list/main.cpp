#include <iostream>
#include <cassert>
#include "ListNode.h"

int main()
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
    std::cout << node;
}