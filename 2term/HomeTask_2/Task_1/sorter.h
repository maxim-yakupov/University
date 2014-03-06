#pragma once

/**
 * @brief The Sorter class
 * @detailed Abstract class of Sorters
 */
class Sorter
{
public:
    /**
     * @brief sort Sorts array in ascending order
     * @param array Array, which we sort in ascending order
     * @param size Number of elements in this array
     */
    virtual void sort(int array[], unsigned int size) = 0;
};
