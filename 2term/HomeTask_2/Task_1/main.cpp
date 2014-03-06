#include <iostream>
#include <ctime>
#include "heapsorter.h"
#include "quicksorter.h"
#include "randomsorter.h"

using namespace std;

void genArray(int array[], int length);

void writeArray(int array[], int length);

int main()
{
    const int arrayLength = 10;
    int array[arrayLength] = {0};
    //writeArray(array, arrayLength);//check of initialization

    cout << "Array consists with " << arrayLength << " elements.\n";
    cout << "Before every sort it will be generated again\n\n";

    HeapSorter heapS;
    genArray(array, arrayLength);
    cout << "Your array: ";
    writeArray(array, arrayLength);
    heapS.sort(array, arrayLength);
    cout << "Result(heap-sort): ";
    writeArray(array, arrayLength);
    cout << endl;

    QuickSorter quickS;
    genArray(array, arrayLength);
    cout << "Your array: ";
    writeArray(array, arrayLength);
    quickS.sort(array, arrayLength);
    cout << "Result(quick-sort): ";
    writeArray(array, arrayLength);
    cout << endl;

    RandomSorter randS;
    genArray(array, arrayLength);
    cout << "Your array: ";
    writeArray(array, arrayLength);
    cout << "Ready?..";
    cin.get();
    randS.sort(array, arrayLength);
    cout << "Result(rand-sort): ";
    writeArray(array, arrayLength);
    cout << endl;

    return 0;
}

/**
 * @brief genArray Generates array's values
 * @param array Array, which we fill
 * @param length Number of elements in this array
 */
void genArray(int array[], int length)
{
    srand(clock());
    for (int i = 0; i < length; i++)
    {
        array[i] = rand() %100;
    };
}

/**
 * @brief writeArray Prints array
 * @param array Array, which we print
 * @param length Number of elements in this array
 */
void writeArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << array[i] << " ";
    };
    cout << endl;
}
