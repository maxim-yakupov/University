#pragma once
#include "list.h"

/*
 * Doubly linked list
 *
 * numeration from zero(0)
 *
 * Based on List class
 */

class DoublyLinkedList : public List
{
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void addValue(int value);//adds last element
    void addPos(int pos, int value);//adds on position or last element
    void deletePos(int pos);//deletes element from position or last element
private:
    struct DLListElement:public ListElement
    {
        DLListElement* prev;
    };
};
