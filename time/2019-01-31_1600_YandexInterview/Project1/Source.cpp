#include <iostream>

// Interview question: add function to reverse list

struct Node {
    Node* next;
    int value;
};

void print(const Node * head)
{
    if (head == nullptr)
    {
        std::cout << "nullptr header" << std::endl;
        return;
    }

    auto cur = head;

    while (head)
    {
        std::cout << "p=" << cur << "; v=" << cur->value;
        if (cur->next == nullptr)
            break;
        std::cout << " -> ";
        cur = cur->next;
    }

    std::cout << std::endl;
}

Node* reverse(Node* head)
{
    if(head == nullptr)
        return head;

    Node * cur = head;
    Node * next = cur->next;
    Node * prev = nullptr;

    while (next != nullptr)
    {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = cur->next;
    }

    cur->next = prev;
    return cur;
}

int main()
{
    Node * head = new Node { nullptr, 1 };
    head->next = new Node { nullptr, 2 };
    head->next->next = new Node { nullptr, 3 };
    print(head);
    Node * reversed = reverse(head);
    print(reversed);
    std::cin.get();
}