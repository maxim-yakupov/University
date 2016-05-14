#pragma once
#include "sorter.h"

/**
 * @brief The QuickSorter class
 * @detailed Sorter, who use Quick sort
 */
class QuickSorter : public Sorter
{
public:
    /**
     * @brief sort Sorts array with Quick sort
     * @param array Array, which we sort in ascending order
     * @param size Number of elements in this array
     */
    void sort(int array[], unsigned int size);
private:
    /**
     * @brief quickSort Recurrent implementation of Quick sort
     * @param array  Array, which we sort
     * @param leftLimiter Number of the most left element of sorting segment
     * @param rightLimiter Number of the most right element of sorting segment
     */
    void quickSort(int array[], int leftLimiter, int rightLimiter);
    /**
     * @brief swap Swaps two elements
     * @param array Array, in which we swap two elements
     * @param first Number of one of swapped elements
     * @param second Number of one of swapped elements
     */
    void swap(int array[],int first, int second);
};
