#include <initializer_list>
#include <ostream>
#include <functional>
#include <deque>

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
        traverseTree(parent->left, func, d + 1);

    if(parent->right != nullptr)
        traverseTree(parent->right, func, d + 1);
}

template <typename T>
void traverseTreeByLevel_doesntWorkTODO(TreeNode<T> * parent, std::function<void(const T &, int)> func)
{
    if(parent == nullptr)
        return;

    int d = 0;
    
    std::deque<TreeNode<T>*> queue;
    queue.push_back(parent);

    while (!queue.empty())
    {
        auto node = queue.front();
        queue.pop_front();
        func(node, 0);

        if(node->left != nullptr)
            queue.push_back(node->left);

        if(node->right != nullptr)
            queue.push_back(node->right);
    }

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
