#pragma once
#include "outputter.h"

/**
 * @brief The ConsoleOutputter class
 * @detailed Prints bypass in console
 */
class ConsoleOutputter : public Outputter
{
public:
    ~ConsoleOutputter();
    bool output(int **array, unsigned int size);
};
