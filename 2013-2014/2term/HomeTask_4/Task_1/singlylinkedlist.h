#pragma once
#include "list.h"

/*
 * Singly linked list
 *
 * numeration from zero(0)
 *
 * Based on List class
 */

class SinglyLinkedList:public List
{
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void addValue(const char *value);//adds last element
    void addPos(int pos, char* value);//adds on position or last element
    void deletePos(int pos);//deletes element from position or last element
protected:
    struct SLListElement:public ListElement
    {
    };
};
