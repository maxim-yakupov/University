#pragma once
#include "sorter.h"

class QuickSorter : public Sorter
{
public:
    void sort(int array[], unsigned int size);
private:
    void quickSort(int array[], int leftLimiter, int rightLimiter);
    void swap(int array[],int first, int second);
};
