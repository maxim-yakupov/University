#include <iostream>

using namespace std;

void printQueue(bool* queue, unsigned int vertices);
void printMatrix(bool** matrix, unsigned int vertices);
void printConnectedComponents(bool **matrix, const unsigned int vertices, bool *&queue, const unsigned int current);

int main()
{
    unsigned int vertices = 0;
    cout << "Write number of vertices: ";
    cin >> vertices;

    bool** matrix = new bool* [vertices];
    for (unsigned int i = 0; i < vertices; i++)
    {
        matrix[i] = new bool [vertices];
    }

    cout << "Write adjacency matrix of size " << vertices << "X" << vertices << endl;

    for (unsigned int i = 0; i < vertices; i++)
    {
        for (unsigned int j = 0; j < vertices; j++)
        {
            cin >> matrix[i][j];
        }
    }

    cout << endl;
    //printMatrix(matrix, vertices);

    bool* queue = new bool [vertices];
    for (unsigned int i = 0; i < vertices; i++)
    {
        queue[i] = true;
    }

    cout << endl;
    cout << "connected components:" << endl;
    for (unsigned int i=0; i < vertices; i++)
    {
        printConnectedComponents(matrix, vertices, queue, i);
        if ((i == vertices - 1) || (queue[i+1])) cout << endl;
    }
    //printQueue(queue, vertices);

    delete[] queue;
    for (unsigned int i = 0; i < vertices; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}

void printConnectedComponents(bool** matrix, const unsigned int vertices, bool*& queue, const unsigned int current)
{
    if (queue[current])
    {
        cout << "!" << current << "!";
        queue[current] = false;
    }
    for (unsigned int j = current+1; j < vertices; j++)
    {
        if ((matrix[current][j]) && (queue[j]))
        {
            printConnectedComponents(matrix, vertices, queue, j);
        }
    }
}

void printQueue(bool* queue, unsigned int vertices)
{
    cout << endl;
    cout << "queue(debug): ";
    for (unsigned int i = 0; i < vertices; i++)
    {
        cout<< queue[i] << " ";
    }
}

void printMatrix(bool** matrix, unsigned int vertices)
{
    cout << "matrix(debug output)" << endl;
    for (unsigned int i = 0; i < vertices; i++)
    {
        for (unsigned int j = 0; j < vertices; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
