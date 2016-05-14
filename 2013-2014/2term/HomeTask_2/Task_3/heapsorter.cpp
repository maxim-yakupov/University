#include "heapsorter.h"

void HeapSorter::sort(int **array, unsigned int width, unsigned int height)
{
    while (width != 1)
    {
        for (int i = width - 1; i >= 1; i--)
        {
            upElemInHeap(array, i, height);
        };
        width--;
        swap(array, 0, width, height);
    };
}

void HeapSorter::upElemInHeap(int **array, int elemOfHeap, unsigned int height)
{
    int parent = (elemOfHeap - 2 + (elemOfHeap % 2)) / 2;
    if ((elemOfHeap != 0) && (array[0][elemOfHeap] > array[0][parent]))
    {
        swap(array, elemOfHeap, parent, height);
        upElemInHeap(array, parent, height);
    };
}

void HeapSorter::swap(int **array, int first, int second, unsigned int height)
{
    for (int i = 0; i < height; i++)
    {
        int temp = array[i][first];
        array[i][first] = array[i][second];
        array[i][second] = temp;
    }
}
