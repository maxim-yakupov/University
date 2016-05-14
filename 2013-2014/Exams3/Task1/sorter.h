#pragma once
#include "comparator.h"

template<class T>
/**
 * @brief The Sorter class
 * @detailed Class, implementated 'Bubble sort'
 */
class Sorter
{
public:
    /**
     * @brief sort Sorts array with 'Bubble sort'
     * @param array Array, which sorts
     * @param size Size of array
     * @param comp Comparator(criterium of sort)
     * @return Sorted array
     */
    static T* sort(const T *array, unsigned int size, const Comparator<T> *comp);
};

template<class T>
T* Sorter<T>::sort(const T *inputArray, unsigned int size, const Comparator<T> *comp)
{
    T* array = new T[size];
    for (unsigned int i = 0; i < size; i++)
    {
        array[i] = inputArray[i];
    }
    for (unsigned int i = 0; i < size - 1; i++)
    {
        for (unsigned int j = 0; j < size - i - 1; j++)
        {
            if (comp->compare(array[j], array[j + 1]))
            {
                T buffer = array[j];
                array[j] = array[j + 1];
                array[j + 1] = buffer;
            }
        }
    }
    return array;
}
