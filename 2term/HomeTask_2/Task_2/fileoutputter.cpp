#include "fileoutputter.h"
#include <fstream>

FileOutputter::FileOutputter()
{
}

FileOutputter::~FileOutputter()
{
}

bool FileOutputter::output(int **array, unsigned int size)
{
    std::ofstream outStream("output.txt");
    if (!outStream) return false;

    int *out = bypass(array, size);
    for (unsigned int i = 0; i < size*size; i++)
    {
        outStream << out[i] << " ";
    }
    delete [] out;
    outStream.close();

    return true;
}
