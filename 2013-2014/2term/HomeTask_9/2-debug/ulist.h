#include "plist.h"
#pragma once

class AddingExistingItem {};

class RemovingNotExistingItem {};

class UList : public PList
{
public:
    UList();
    ~UList();
    void add(int value, int num);
    int length();
    void del(int num);
    void printList();
    int returnValue(int num);
    void removeList();
    void swap(int i, int j);
    bool exist(int value);
    void delValue(int value);
};
