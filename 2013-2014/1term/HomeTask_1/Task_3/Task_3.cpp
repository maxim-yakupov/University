#include <iostream>
#include "stdlib.h"

using namespace std;

void genArray(int array[], int amountInLeftPart, int amountInRightPart, bool fl);
//
void readArray(int array[], int amountInLeftPart, int amountInRightPart);
//
void swap(int array[], int start, int condition, int delta, int amountInLeftPart);
//
void writeArray(int array[], int amountInLeftPart, int amountInRightPart, bool generate);
//

int main()
{
    const int arrayLength = 10;
    int array[arrayLength];

    cout << "Enter limiters 'm' and 'n' (m+n <= " << arrayLength << " ): ";
    int amountInLeftPart = arrayLength / 2;
    int amountInRightPart = arrayLength / 2;
    cin >> amountInLeftPart >> amountInRightPart;
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
            readArray(array, amountInLeftPart, amountInRightPart);
            break;
        };
        //
        case 'g':
        {
            genArray(array, amountInLeftPart, amountInRightPart, true);
            cout << "Your array: ";
            writeArray(array, amountInLeftPart, amountInRightPart, true);
            break;
        };
        //
        default:
        {
            genArray(array, amountInLeftPart, amountInRightPart, false);
            cout << "Your array: ";
            writeArray(array, amountInLeftPart, amountInRightPart, true);
            break;
        };
    };
    //
    swap(array, 0, (amountInLeftPart - 1) / 2, 0, amountInLeftPart);
    //
    swap(array, amountInLeftPart, (amountInLeftPart - 1 + (amountInRightPart / 2)), amountInRightPart + amountInLeftPart, amountInLeftPart);
    //
    swap(array, 0, (-1 + (amountInLeftPart + amountInRightPart) / 2), amountInRightPart, amountInLeftPart);
    //
    cout << "Array after transposition: ";
    writeArray(array, amountInLeftPart, amountInRightPart, false);
    return 0;
}

void genArray(int array[], int amountInLeftPart, int amountInRightPart, bool fl)
{
    int seed = 911;
    if (fl)
    {
        cout << "Enter seed(number) for random generation: ";
        cin >> seed;
        cout << endl;
    };
    srand(seed);
    for (int i = 0; i < amountInLeftPart + amountInRightPart; i++)
    {
        array[i] = rand() %100;
    };
}

void readArray(int array[], int amountInLeftPart, int amountInRightPart)
{
    cout << "Your array: ";
    for (int i = 0; i < amountInLeftPart + amountInRightPart; i++)
    {
        cin >> array[i];
    };
    cout << endl;
}

void swap(int array[],int start, int condition, int delta, int amountInLeftPart)
{
    int temp = 0;
    for (int i = start; i <= condition; i++)
    {
        temp = array[i];
        array[i] = array[amountInLeftPart - 1 - i + delta];
        array[amountInLeftPart - 1 - i + delta] = temp;
    };
}

void writeArray(int array[], int amountInLeftPart, int amountInRightPart, bool generate)
{
    for (int i = 0; i < amountInLeftPart + amountInRightPart; i++)
    {
        cout << array[i] << " ";
        if (((i == amountInLeftPart - 1) && (generate)) || ((i == amountInRightPart - 1) && !(generate))) // beautiful output
        {
            cout << "| ";
        };
    };
    cout << endl;
}
