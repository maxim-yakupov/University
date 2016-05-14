#include <iostream>

using namespace std;

void writeArray(int** array, unsigned int h, unsigned int w);
void writePoints(int** array, unsigned int h, unsigned int w, int* min, int* max);

int main()
{
    cout << "Enter width of array: ";
    unsigned int w = 1;
    cin >> w;
    cout << "Enter height of array: ";
    unsigned int h = 1;
    cin >> h;
    int** array = new int* [h];
    for (unsigned int i = 0; i < h; i++)
    {
        array[i] = new int[w];
    }

    int* min = new int[h];
    int* max = new int[w];

    cout << "Write elements of array(only int):" << endl;
    for (unsigned int i = 0; i < h; i++)
    {
        for (unsigned int j = 0; j < w; j++)
        {
            cout << "(" << i << "," << j << "):";
            cin >> array[i][j];
            if ((!j) || (min[i] > array[i][j]))
            {
                min[i] = array[i][j];
            }
            if ((!i) || (max[j] < array[i][j]))
            {
                max[j] = array[i][j];
            }
        }
    }
    writeArray(array, h, w);

    cout << "Minimal elements of each row" << endl;
    for (unsigned int j = 0; j < h; j++)
    {
        cout << " " << min[j];
    }
    cout << "\nMaximal elements of each column" << endl;
    for (unsigned int j = 0; j < w; j++)
    {
        cout << " " << max[j];
    }

    writePoints(array, h, w, min, max);

    delete [] min;
    delete [] max;
    for (unsigned int i = 0; i < h; i++)
    {
        delete [] array[i];
    }
    delete [] array;
    return 0;
}

void writePoints(int** array, unsigned int h, unsigned int w, int* min, int* max)
{
    cout << "\nSedlovye tochki:" << endl;
    for (unsigned int i = 0; i < h; i++)
    {
        for (unsigned int j = 0; j < w; j++)
        {
            if ((array[i][j] == min[i]) && (array[i][j] == max[j]))
            {
                cout << "(" << i << "," << j << "): " << array[i][j] << endl;
            }
        }
    }
}

void writeArray(int** array, unsigned int h, unsigned int w)
{
    cout << "===Printing of array===" << endl;
    for (unsigned int i = 0; i < h; i++)
    {
        cout << array[i][0];
        for (unsigned int j = 1; j < w; j++)
        {
            cout << " " << array[i][j];
        }
        cout << endl;
    }
    cout << "=======================" << endl;
}
