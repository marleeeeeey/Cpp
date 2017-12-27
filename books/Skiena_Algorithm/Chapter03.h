#pragma once

#include "StdHelper.hpp"
#include "SkienaShared.h"

namespace SkienaChapter03
{
    using namespace SkienaShared;

    struct tree
    {
        item_type item   = 0;
        tree *    parent = nullptr;
        tree *    left   = nullptr;
        tree *    right  = nullptr;
    };        

    // [стр. 97] Алгоритм рекурсивного поиска произвольного элемента в двоичном дереве
    tree * search_tree(tree * l, item_type x)
    {
        if (l == nullptr) 
            return nullptr;

        if (l->item == x) 
            return l;

        if (x < l->item)
            return (search_tree(l->left, x));
        else
            return (search_tree(l->right, x));
    }

    // [стр. 98] Поиск наименьшего значения в двоичном дереве
    tree * find_minimum(tree * t)
    {
        tree * min;

        if (t == nullptr) 
            return nullptr;

        min = t;

        while (min->left != nullptr)
        {
            min = min->left;
        }

        return min;
    }

    // [стр. 98] Рекурсивный алгоритм симметричного обхода в двоичном дереве
    void traverse_tree(tree * t)
    {
        if (t != nullptr)
        {
            traverse_tree(t->left);
            process_item(t->item);
            traverse_tree(t->right);
        }
    }


    // [стр. 99] Вставка узла в двоичное дерево   
    // l - указатель на указатель, связывающий поддерево с остальной частью
    //     (указатель на поддерево)
    // parent - указатель на родительский узел, содержащий l
    void insert_tree(tree ** l, item_type x, tree * parent)
    {
        if (*l == nullptr)
        {
            tree * p  = new tree;
            p->item   = x;
            p->left   = nullptr;
            p->right  = nullptr;
            p->parent = parent;
            *l        = p;
            return;
        }

        tree * curTree = *l;

        if (x < (*l)->item)
            insert_tree(&(curTree->left), x, *l);
        else
            insert_tree(&(curTree->right), x, *l);
    }

    tree * getTree()
    {
        static bool isFirstRun = true;
        static tree * t = nullptr;

        if (isFirstRun)
        {
            t = new tree;
            t->item = -3;
            t->parent = nullptr;
            
            tree * t_left = new tree;
            t_left->item = -5;

            tree * t_right = new tree;
            t_right->item = -1;

            t->left = t_left;
            t->right = t_right;
            

            isFirstRun = false;
        }

        return t;
    }

    void processNewItem(item_type item)
    {
        AFUN;
        AVAR(item);
    }

    void resolve()
    {
        AFUN;
                
        enum 
        {
            e_count = 10,
            e_maxValue = e_count * 10,
        };

        std::set<item_type> vars;

        for (int i = 0; i < e_count; i++)
        {
            item_type newItem = getRandom<int>(1, e_maxValue);

            if (vars.find(newItem) == vars.end())
                processNewItem(newItem);

            vars.insert(newItem);
        }
    }
}