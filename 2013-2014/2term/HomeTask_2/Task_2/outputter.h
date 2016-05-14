#pragma once

/**
 * @brief The Outputter class
 * @detailed Class, which prints matrix in spiral bypass
 */
class Outputter
{
public:
    virtual ~Outputter();
    /**
     * @brief output Printing out way of bypass
     * @param array Matrix [size X size]
     * @param size Size of the side of square matrix
     * @return 'true' if all OK & 'false' if occures error of open file 'output.txt'
     */
    virtual bool output(int **array, unsigned int size) = 0;
protected:
    /**
     * @brief bypass Spiral bypass of square matrix
     * @param array Matrix [size X size]
     * @param size Size of the side of square matrix
     * @return Pointer on 1D array, which saves way of bypass
     */
    int* bypass(int **array, unsigned int size);
};
