#pragma once
#include "sorter.h"

class RandomSorter : public Sorter
{
public:
    void sort(int array[], unsigned int size);
private:
    void swap(int array[],int first, int second);
    bool check(int array[], unsigned int size);
};
