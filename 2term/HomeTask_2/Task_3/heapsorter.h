#pragma once
#include "sorter.h"

/**
 * @brief The HeapSorter class
 * @detailed Sorter, who use Heap sort
 */
class HeapSorter : public MatrixSorter
{
public:
    /**
     * @brief sort Sorts array with Heap sort
     * @param array Array(2D), which we sort
     * @param width Number of elements in this matrix's row
     * @param height Number of elements in this matrix's column
     */
    void sort(int **array, unsigned int width, unsigned int height);
private:
    /**
     * @brief upElemInHeap Puts column upper in the tree if it should be there
     * @param array Matrix, in which we 'float' column
     * @param elemOfHeap Number of column, which we put upper
     * @param height Number of elements in this matrix's column
     */
    void upElemInHeap(int **array, int elemOfHeap, unsigned int height);
    /**
     * @brief swap Swaps two columns
     * @param array Matrix, in which we swap two columns
     * @param first Number of one of swapped columns
     * @param second Number of one of swapped columns
     */
    void swap(int **array, int first, int second, unsigned int height);
};
