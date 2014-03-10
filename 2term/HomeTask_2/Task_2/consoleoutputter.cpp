#include "consoleoutputter.h"
#include <iostream>

ConsoleOutputter::~ConsoleOutputter()
{
}

bool ConsoleOutputter::output(int **array, unsigned int size)
{
    int *out = bypass(array, size);
    for (unsigned int i = 0; i < size*size; i++)
    {
        std::cout << out[i] << " ";
    }
    delete [] out;
    return true;
}
