#pragma once

/*
 * Singly linked list
 *
 * numeration from zero(0)
 *
 * Empty list don't exists!
 */

class List
{
public:
    List(int value);
    virtual ~List();
    int length();//returns length of list
    virtual void addValue(int value);//adds last element
    virtual void addPos(int pos, int value);//adds on position or last element
    virtual void deletePos(int pos);//deletes element from position or last element
    virtual void deleteList();//deletes all elements of list exept first
    void print();//prints list
protected:
    int elemValue;
    List* next;
};
