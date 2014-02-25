#include "stdio.h"

using namespace std;

int strlen(char* str);
void swap(char* array, int first, int second);
void upElemInHeap(char* array, int elemOfHeap);
void heapSort(char* array, int heapLength);

int main()
{
    char* str = new char[100] {'\0'};
    printf("Write number: ");
    scanf("%s", str);
    int length = strlen(str);
    if (length != 1)
    {
        heapSort(str, length);
        if ((str[0] == '0') && (length != 1))
        {
            int firstNotZero = 1;
            while (str[firstNotZero] == '0')
            {
                firstNotZero++;
            };
            swap(str, 0, firstNotZero);
        };
    };
    printf("Result:       %s", str);
    delete [] str;
    return 0;
}

int strlen(char* str)
{
    int length = 0;
    while (*(str + length) != '\0')
    {
        length++;
    };
    return length;
}

void swap(char* array,int first, int second)
{
    char temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

void upElemInHeap(char* array, int elemOfHeap)
{
    int parent = (elemOfHeap - 2 + (elemOfHeap % 2)) / 2;
    if ((elemOfHeap != 0) && (array[elemOfHeap] > array[parent]))
    {
        swap(array, elemOfHeap, parent);
        upElemInHeap(array, parent);
    };
}

void heapSort(char* array, int heapLength)
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
