#include <iostream>
#include "stdlib.h"

using namespace std;

void readArray(int array[], int length);
void genArray(int array[], int length, bool fl);
void swap(int array[],int first, int second);
void writeArray(int array[], int length);
void quickSort(int array[], int leftLimiter, int rightLimiter);

int main()
{
    const int arrayLength = 10;
    int array[arrayLength];

    cout << "Array consists with " << arrayLength << " elements.";
    cout << endl;
    //
    cout << "Do you want to [E]nter elements of array or [g]enerate them for you? ";
    char choice = '0';
    cin >> choice;
    cout << endl;
    //
    switch (choice)
    {
        case 'E':
        {
            readArray(array, arrayLength);
            break;
        };
        //
        case 'g':
        {
            genArray(array, arrayLength, true);
            cout << "Your array: ";
            writeArray(array, arrayLength);
            break;
        };
        //
        default:
        {
            genArray(array, arrayLength, false);
            cout << "Your array: ";
            writeArray(array, arrayLength);
            break;
        };
    };

    quickSort(array, 0, arrayLength - 1);
    cout << endl;
    cout << "Result: ";
    writeArray(array, arrayLength);
    return 0;
}

void genArray(int array[], int length, bool fl)
{
    int seed = 911;
    if (fl)
    {
        cout << "Enter seed(number) for random generation: ";
        cin >> seed;
        cout << endl;
    };
    srand(seed);
    for (int i = 0; i < length; i++)
    {
        array[i] = rand() %100;
    };
}

void readArray(int array[], int length)
{
    cout << "Your array: ";
    for (int i = 0; i < length; i++)
    {
        cin >> array[i];
    };
    cout << endl;
}

void swap(int array[],int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}

void writeArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << " ";
    };
    cout << endl;
}

void quickSort(int array[], int leftLimiter, int rightLimiter)
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
