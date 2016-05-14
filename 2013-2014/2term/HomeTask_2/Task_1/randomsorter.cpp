#include "randomsorter.h"
#include <iostream>
#include <ctime>

void RandomSorter::sort(int array[], unsigned int size)
{
    while (!check(array, size))
    {
        srand(clock());
        swap(array, rand() %size, rand() %size);
    }
}

void RandomSorter::swap(int array[], int first, int second)
{
    std::cout << "try swap " << first << " and " << second << std::endl;
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

bool RandomSorter::check(int array[], unsigned int size)
{
    if (size == 1) return true;
    for (unsigned int i = 0; i < size; i++)
    {
        if (array[i] > array[i+ 1])
            return false;
    }
    return true;
}
