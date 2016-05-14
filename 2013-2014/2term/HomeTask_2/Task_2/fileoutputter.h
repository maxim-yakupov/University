#pragma once
#include "outputter.h"

/**
 * @brief The FileOutputter class
 * @detailed Prints bypass in file 'output.txt'
 */
class FileOutputter : public Outputter
{
public:
    ~FileOutputter();
    bool output(int **array, unsigned int size);
};
