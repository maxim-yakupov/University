#pragma once

/**
 * @brief The MatrixSorter class
 * @detailed Abstract class of Matrix Sorters
 */
class MatrixSorter
{
public:
    /**
     * @brief sort Sorts 2D array
     * @param array Array(2D), which we sort
     * @param width Number of elements in this matrix's row
     * @param height Number of elements in this matrix's column
     */
    virtual void sort(int **array, unsigned int width, unsigned int height) = 0;
};
