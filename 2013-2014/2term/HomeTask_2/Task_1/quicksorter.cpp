#include "quicksorter.h"

void QuickSorter::sort(int array[], unsigned int size)
{
    quickSort(array, 0, size);
}

void QuickSorter::quickSort(int array[], int leftLimiter, int rightLimiter)
{
    if (leftLimiter == rightLimiter - 1)
    {
        if (array[leftLimiter] > array[rightLimiter])
        {
            swap(array, leftLimiter, rightLimiter);
        };
    }
    else if (leftLimiter != rightLimiter)
    {
        const int base = array[rightLimiter];
        int left = leftLimiter;
        int right = rightLimiter;
        while (left <= right)
        {
            while ((array[left] <= base) && (left <= rightLimiter))
            {
                left++;
            };
            while ((array[right] > base) && (right >= leftLimiter))
            {
                right--;
            };
            if (left < right)
            {
                swap(array, left, right);
            }
            else
            {
                if (left <= rightLimiter)
                {
                    quickSort(array, left, rightLimiter);
                    quickSort(array, leftLimiter, left - 1);
                }
                else
                {
                    quickSort(array, leftLimiter, right - 1);
                    quickSort(array, right, rightLimiter);
                };
            };
        };
    };
}

void QuickSorter::swap(int array[], int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}
