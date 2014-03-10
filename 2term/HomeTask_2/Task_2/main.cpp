#include <iostream>
#include <ctime>
#include "consoleoutputter.h"
#include "fileoutputter.h"

using namespace std;

void genArray(int **array, unsigned int width, unsigned int height);

void writeArray(int **array, unsigned int width, unsigned int height);

int main()
{
    int ticks = clock();
    while (ticks + 1000 - clock() > 0);//delay ~1000 ms

    unsigned int size = 3;

    cout << "Write size of array(size % 2 should be equal 1): ";
    cin >> size;

    int **array = new int*[size];
    for (unsigned int i = 0; i < size; i++)
    {
        array[i] = new int[size];
    }

    cout << "Array's size: " << size << "x" << size << "(width x height) elements.\n";
    cout << "Before every sort it will be generated again\n\n";

    genArray(array, size, size);
    cout << "Your array: \n";
    writeArray(array, size, size);
    cout << endl;

    bool typeOfOutput = true;
    cout << "If you want to see result in console, type 1\n";
    cout << "If you want to see result in file output.txt, type 0\n";
    cin >> typeOfOutput;

    Outputter *outputter = nullptr;
    if (typeOfOutput)
    {
        outputter = new ConsoleOutputter;
    }
    else
    {
        outputter = new FileOutputter;
    }

    if (outputter->output(array, size))
    {
        if (!typeOfOutput)
        {
            cout << "Result in file 'output.txt'";
        }
    }
    else
    {
        cout << "'output.txt' open error";
    }

    delete outputter;

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

