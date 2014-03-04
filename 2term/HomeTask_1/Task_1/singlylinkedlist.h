#pragma once
#include "list.h"

/*
 * Singly linked list
 *
 * numeration from zero(0)
 *
 * Based on List class
 */

struct SLListElement:public ListElement
{
};

class SinglyLinkedList:public List
{
public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void addValue(int value);//adds last element
    void addPos(int pos, int value);//adds on position or last element
    void deletePos(int pos);//deletes element from position or last element
};
