#pragma once
#include "sorter.h"

class HeapSorter : public Sorter
{
public:
    void sort(int array[], unsigned int size);
private:
    void upElemInHeap(int array[], int elemOfHeap);
    void swap(int array[],int first, int second);
};
