#pragma once

class List
{
public:
    virtual void add(int value, int num) = 0;
    virtual int length() = 0;
    virtual void del(int num) = 0;
    virtual void printList() = 0;
    virtual int returnValue(int num) = 0;
    virtual void removeList() = 0;
    virtual void swap(int i, int j) = 0;
    virtual ~List(){}
};
