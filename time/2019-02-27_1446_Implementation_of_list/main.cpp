#include <iostream>
#include <cassert>
#include "ListNode.h"
#include <functional>

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

template <typename T>
void traverseTree(TreeNode<T> * parent, std::function<void(const T &, int)> func, int d = 0)
{
    if(parent == nullptr)
        return;
    
    func(parent->value, d);

    if(parent->left != nullptr)
        traverseTree(parent->left, func, d+1);

    if(parent->right != nullptr)
        traverseTree(parent->right, func, d+1);
}

template<typename T>
TreeNode<T> * generateTree(std::initializer_list<T> list)
{
    bool isFirstValue = true;
    TreeNode<T> * node = new TreeNode<T>();
    for(auto e : list)
    {
        if(isFirstValue)
        {
            node->value = e;
            isFirstValue = false;
            continue;
        }

        insertTree(node, e);
    }

    return node;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, TreeNode<T> * tree)
{
    std::function<void(const T &, int)> fun = [&os](const T & val, int d)
    {
        os << val << "(" << d << ")" << ", ";
    };

    traverseTree(tree, fun);

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
    TreeNode<int> * tree = generateTree({ 4, 5, 6, 7, 1, 2, 3 });
    std::cout << tree;
    std::cin.get();
}