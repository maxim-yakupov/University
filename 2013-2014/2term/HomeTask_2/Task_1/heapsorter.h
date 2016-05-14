#pragma once
#include "sorter.h"

/**
 * @brief The HeapSorter class
 * @detailed Sorter, who use Heap sort
 */
class HeapSorter : public Sorter
{
public:
    /**
     * @brief sort Sorts array with Heap sort
     * @param array Array, which we sort in ascending order
     * @param size Number of elements in this array
     */
    void sort(int array[], unsigned int size);
private:
    /**
     * @brief upElemInHeap Puts element upper in the tree if it should be there
     * @param array Array, in which we 'float' element
     * @param elemOfHeap Number of element, which we put upper
     */
    void upElemInHeap(int array[], int elemOfHeap);
    /**
     * @brief swap Swaps two elements
     * @param array Array, in which we swap two elements
     * @param first Number of one of swapped elements
     * @param second Number of one of swapped elements
     */
    void swap(int array[],int first, int second);
};
