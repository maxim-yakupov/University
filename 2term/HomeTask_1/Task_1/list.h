#pragma once

/*
 * List abstract class
 */

struct ListElement
{
    int elemValue;
    ListElement* next;
};

class List
{
public:
    List();
    virtual ~List();
    ListElement* getPos(int pos);
    unsigned int length();//returns length of list
    virtual void addValue(int value) = 0;//adds last element
    virtual void addPos(int pos, int value) = 0;//adds on position or last element
    virtual void deletePos(int pos) = 0;//deletes element from position or last element
    void print();//prints list
protected:
    ListElement* head;
    unsigned int size;
};
