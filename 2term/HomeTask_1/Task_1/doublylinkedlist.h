#pragma once
#include "list.h"

/*
 * Doubly linked list
 *
 * numeration from zero(0)
 *
 * Empty list don't exists!
 *
 * Based on List class(Singly linked list)
 */

class DoublyLinkedList : public List
{
public:
    DoublyLinkedList(int value);
    ~DoublyLinkedList();
    void addValue(int value);//adds last element
    void addPos(int pos, int value);//adds on position or last element
    void deletePos(int pos);//deletes element from position or last element
    virtual void deleteList();//deletes all elements of list exept first
protected:
    DoublyLinkedList* prev;
};
