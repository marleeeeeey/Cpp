#include <iostream>
#include <cassert>
#include "ListNode.h"

template<typename T>
struct TreeNode
{
    TreeNode * parent = nullptr;
    TreeNode * left = nullptr;
    TreeNode * right = nullptr;
    T value;
};

template<typename T>
TreeNode<T> * insertTree(TreeNode<T> * parent, T value)
{
    if(value <= parent->value)
    {
        if(parent->left == nullptr)
        {
            auto node = new TreeNode<T>();
            node->value = value;
            node->parent = parent;
            parent->left = node;
            return node;
        }
        else
        {
            return insertTree(parent->left, value);
        }
    }
    else
    {
        if(parent->right == nullptr)
        {
            auto node = new TreeNode<T>();
            node->value = value;
            node->parent = parent;
            parent->right = node;
            return  node;
        }
        else
        {
            return insertTree(parent->right, value);
        }
    }
}

template<typename T>
TreeNode<T> * generateTree(std::initializer_list<T> list)
{
    TreeNode * tree = new TreeNode();
    for(auto e : list)
    {

    }
    // TODO   
}

template<typename T>
std::ostream & operator<<(std::ostream & os, TreeNode<T> * tree)
{


    return os;
}

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

int main()
{
    // TODO
}