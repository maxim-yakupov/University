#include "stdio.h"

using namespace std;

void swap(int *array, int first, int second);
void upElemInHeap(int *array, int elemOfHeap);
void heapSort(int *array, int heapLength);

int main()
{
    printf("Write number of elements: ");
    int length = 1;
    scanf("%d", &length);

    int* array = new int[length];
    printf("Write elements of array:\n");
    for (int i = 0; i < length; i++)
    {
        scanf("%d", &array[i]);
    };

    int maxIndex = length - 1;
    if (length != 1)
    {
        heapSort(array, length);
        while (maxIndex > 0)
        {
            if (array[maxIndex] == array[maxIndex - 1])
            {
                break;
            }
            else
            {
                maxIndex--;
            };
        };
    };

    if (maxIndex != 0)
    {
        printf("Max element, which meets more, than one time in array is %d", array[maxIndex]);
    }
    else
    {
        printf("There is not any element, which meets more, than one time in array");
    };

    delete [] array;
    return 0;
}

void swap(int* array,int first, int second)
{
    char temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

void upElemInHeap(int* array, int elemOfHeap)
{
    int parent = (elemOfHeap - 2 + (elemOfHeap % 2)) / 2;
    if ((elemOfHeap != 0) && (array[elemOfHeap] > array[parent]))
    {
        swap(array, elemOfHeap, parent);
        upElemInHeap(array, parent);
    };
}

void heapSort(int* array, int heapLength)// O(n*log n)
{
    while (heapLength != 1)
    {
        for (int i = heapLength - 1; i >= 1; i--)
        {
            upElemInHeap(array, i);
        };
        heapLength--;
        swap(array, 0, heapLength);
    };
}

