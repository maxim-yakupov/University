#pragma once
#include "binarytree.h"

namespace lists
{
    struct ListElement
    {
        BinaryTreeAPI::TreeNode* node;
        ListElement* next;
    };
    struct List
    {
        ListElement* head;
        int length;
    };
    List* initList(BinaryTreeAPI::TreeNode* node);
    ListElement* getElement(int pos, List *list);
    void addElement(ListElement* prev, BinaryTreeAPI::TreeNode* node, List* list);
    void deleteElement(ListElement *prev, List *list);
    void deleteList(List *list);
}

