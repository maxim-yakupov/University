#include <iostream>
#include <ctime>
#include "heapsorter.h"

using namespace std;

void genArray(int **array, unsigned int width, unsigned int height);

void writeArray(int **array, unsigned int width, unsigned int height);

int main()
{
    int ticks = clock();
    while (ticks + 1000 - clock() > 0);//delay ~1000 ms

    unsigned int width = 3;
    unsigned int height = 4;

    cout << "Write size of array\nWidth: ";
    cin >> width;
    cout << "Height: ";
    cin >> height;

    int **array = new int*[height];
    for (unsigned int i = 0; i < height; i++)
    {
        array[i] = new int[width];
    }

    cout << "Array's size: " << width << "x" << height << "(width x height) elements.\n";
    cout << "Before every sort it will be generated again\n\n";

    HeapSorter heapS;
    genArray(array, width, height);
    cout << "Your array: \n";
    writeArray(array, width, height);
    cout << endl;
    heapS.sort(array, width, height);
    cout << "Result(heap-sort): \n";
    writeArray(array, width, height);
    cout << endl;

    for (unsigned int i = 0; i < height; i++)
    {
        delete [] array[i];
    }
    delete [] array;

    return 0;
}

/**
 * @brief genArray Generates matrix's values
 * @param array Array, which we fill
 * @param width Number of elements in this matrix's row
 * @param height Number of elements in this matrix's column
 */
void genArray(int **array, unsigned int width, unsigned int height)
{
    srand(clock());
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            array[i][j] = rand() %100;
        };
    }
}

/**
 * @brief writeArray Prints 2D array
 * @param array Array, which we print
 * @param width Number of elements in this matrix's row
 * @param height Number of elements in this matrix's column
 */
void writeArray(int **array, unsigned int width, unsigned int height)
{
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            cout << array[i][j] << " ";
        };
        cout << endl;
    }
}
