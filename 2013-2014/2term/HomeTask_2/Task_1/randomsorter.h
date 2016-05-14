#pragma once
#include "sorter.h"

/**
 * @brief The RandomSorter class
 * @detailed Sorter, who use Random sort
 */
class RandomSorter : public Sorter
{
public:
    /**
     * @brief sort Sorts array with Random sort
     * @detailed Swaps two elements and check if sorted
     * @param array Array, which we sort in ascending order
     * @param size Number of elements in this array
     */
    void sort(int array[], unsigned int size);
private:
    /**
     * @brief swap Swaps two elements
     * @param array Array, in which we swap two elements
     * @param first Number of one of swapped elements
     * @param second Number of one of swapped elements
     */
    void swap(int array[],int first, int second);
    /**
     * @brief check Checks array if it sorted
     * @param array Array, which checks
     * @param size  Number of elements in this array
     * @return 'true' if sorted, 'false' in other way
     */
    bool check(int array[], unsigned int size);
};
