#include <iostream>
#include <stdlib.h>//abs()

using namespace std;

void readArray(int array[], int length);
void genArray(int array[], int length, bool fl);
void swap(int array[],int first, int second);
void writeArray(int array[], int length);
void upElemInHeap(int array[], int elemOfHeap);
void heapSort(int array[], int heapLength);

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

    heapSort(array, arrayLength);

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

void upElemInHeap(int array[], int elemOfHeap)
{
    int parent = (elemOfHeap - 2 + (elemOfHeap % 2)) / 2;
    if ((elemOfHeap != 0) && (array[elemOfHeap] > array[parent]))
    {
        swap(array, elemOfHeap, parent);
        upElemInHeap(array, parent);
    };
}

void heapSort(int array[], int heapLength)
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
