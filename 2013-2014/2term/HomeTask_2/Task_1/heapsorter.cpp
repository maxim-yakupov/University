#include "heapsorter.h"

void HeapSorter::sort(int array[], unsigned int size)
{
    while (size != 1)
    {
        for (int i = size - 1; i >= 1; i--)
        {
            upElemInHeap(array, i);
        };
        size--;
        swap(array, 0, size);
    };
}

void HeapSorter::upElemInHeap(int array[], int elemOfHeap)
{
    int parent = (elemOfHeap - 2 + (elemOfHeap % 2)) / 2;
    if ((elemOfHeap != 0) && (array[elemOfHeap] > array[parent]))
    {
        swap(array, elemOfHeap, parent);
        upElemInHeap(array, parent);
    };
}

void HeapSorter::swap(int array[],int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}
