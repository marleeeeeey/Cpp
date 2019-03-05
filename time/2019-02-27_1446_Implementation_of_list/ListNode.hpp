#include <initializer_list>
#include <ostream>

template <typename T>
struct ListNode
{
    ListNode * next = nullptr;
    T value = T();
};

template<typename T>
struct List
{
    ListNode<T> * head;
};

template<typename T>
std::ostream & operator<<(std::ostream & os, const ListNode<T> * list)
{
    auto node = list;
    os << "[";
    while(node != nullptr)
    {
        os << node->value << ", ";
        node = node->next;
    }
    os << "\b\b]";
    return os;
}

template<typename T>
ListNode<T> * generateList(std::initializer_list<T> init)
{
    ListNode<T> * head = nullptr;
    ListNode<T> * cur = nullptr;
    ListNode<T> * prev = nullptr;

    for(const auto elem : init)
    {
        cur = new ListNode<T>();
        cur->value = elem;
        if(prev != nullptr)
            prev->next = cur;
        else
            head = cur;
        prev = cur;
    }

    return head;
}

template<typename T>
ListNode<T> * searchNode(ListNode<T> * list, T value, ListNode<T> ** outPrev = nullptr)
{
    auto node = list;
    while(node != nullptr)
    {
        if(node->value == value)
            return node;

        if(outPrev != nullptr)
            *outPrev = node;

        node = node->next;
    }

    return nullptr;
}

template<typename T>
ListNode<T> * insertNode(ListNode<T> ** list, T value)
{
    if(list == nullptr)
        throw std::logic_error("list doesn't exist");

    auto newNode = new ListNode<T>();
    newNode->value = value;
    newNode->next = *list;
    *list = newNode;

    return newNode;
}

template<typename T>
ListNode<T> * removeNode(ListNode<T> ** list, T value)
{
    ListNode<T> ** ptrToPrev = new ListNode<T>*();
    auto node = searchNode(*list, value, ptrToPrev);

    if(node == nullptr)
        return nullptr;

    auto cur = node->next;
    if(*ptrToPrev != nullptr)
        (*ptrToPrev)->next = cur;
    if(node == *list)
        *list = cur;
    delete node;
    delete ptrToPrev;

    return cur;
}

template<typename T>
bool isEqual(const ListNode<T> * left, const ListNode<T> * right)
{
    auto leftNode = left;
    auto rightNode = right;

    while(true)
    {
        if(leftNode == nullptr && rightNode == nullptr)
            return  true;

        if(leftNode == nullptr && rightNode != nullptr
            || leftNode != nullptr && rightNode == nullptr)
            return  false;

        if(leftNode->value != rightNode->value)
            return  false;

        leftNode = leftNode->next;
        rightNode = rightNode->next;
    }

    return true;
}
