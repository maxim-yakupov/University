#include <iostream>
#include <fstream>

using namespace std;

bool getInFileInformation(ifstream &infile);
void printMatrix(unsigned int** matrix, unsigned int vertices);

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }

    unsigned int vertices = 0;
    infile >> vertices;
    cout << "number of vertices: " << vertices;

    unsigned int maxCost = 0;
    unsigned int** matrix = new unsigned int* [vertices];
    for (unsigned int i = 0; i < vertices; i++)
    {
        matrix[i] = new unsigned int [vertices];
        for (unsigned int j = 0; j < vertices; j++)
        {
            infile >> matrix[i][j];
            if (maxCost < matrix[i][j])
            {
                maxCost = matrix[i][j];
            }
        }
    }

    cout << "\nBase matrix";
    printMatrix(matrix, vertices);

    unsigned int** minSpanningTreeMatrix = new unsigned int* [vertices];
    for (unsigned int i = 0; i < vertices; i++)
    {
        minSpanningTreeMatrix[i] = new unsigned int [vertices];
        for (unsigned int j = 0; j < vertices; j++)
        {
            minSpanningTreeMatrix[i][j] = 0;
        }
    }

    bool* isAdded = new bool[vertices];
    isAdded[0] = true;
    for (unsigned int i = 1; i < vertices; i++)
    {
        isAdded[i] = false;
    }

    unsigned int verticesForAdd = vertices - 1;
    while (verticesForAdd)
    {
        unsigned int baseVertex = 0;
        unsigned int vertexForAdd = 0;
        unsigned int minCost = maxCost + 1;

        for (unsigned int i = 0; i < vertices; i++)
        {
            if (isAdded[i])
            {
                for (unsigned int j = 0; j < vertices; j++)
                {
                    if (!isAdded[j] && matrix[i][j])
                    {
                        if (matrix[i][j] < minCost)
                        {
                            minCost = matrix[i][j];
                            vertexForAdd = j;
                            baseVertex = i;
                        }
                    }
                }
            }
        }
        minSpanningTreeMatrix[baseVertex][vertexForAdd] = minCost;
        minSpanningTreeMatrix[vertexForAdd][baseVertex] = minCost;
        isAdded[vertexForAdd] = true;

        verticesForAdd--;
    }

    cout << "\nMinimal Spanning Tree Matrix";
    printMatrix(minSpanningTreeMatrix, vertices);

    //output of links(extra visualisation)
    unsigned int summaryWeight = 0;
    for (unsigned int i = 0; i < vertices; i++)
    {
        for (unsigned int j = i + 1; j < vertices; j++)
        {
            if (minSpanningTreeMatrix[i][j])
            {
                cout << "[" << i << "] --" << minSpanningTreeMatrix[i][j] << "-- [" << j << "]" << endl;
                summaryWeight += minSpanningTreeMatrix[i][j];
            }
        }
    }
    cout << "Summary weight = " << summaryWeight;
    //

    delete [] isAdded;

    for (unsigned int i = 0; i < vertices; i++)
    {
        delete [] minSpanningTreeMatrix[i];
    }
    delete [] minSpanningTreeMatrix;

    for (unsigned int i = 0; i < vertices; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;

    infile.close();
    return 0;
}

bool getInFileInformation(ifstream &infile)
{
    cout << "Write file name(for input)[only utf-8 chars!]: ";
    char destination[100] = {'\0'};
    cin.getline(destination, 100);
    cout << "Trying to read file '" << destination << "' . . ." << endl;
    infile.open(destination);
    if (!infile.is_open())
    {
        cout << "Ups, i can't read your file! (maybe it is in wrong place)" << endl;
        return 1;
    }
    else
    {
        cout << "File successfuly loaded" << endl;
    }
    cout << endl;
    return 0;
}

void printMatrix(unsigned int** matrix, unsigned int vertices)
{
    cout << "\nmatrix(debug output)" << endl;
    for (unsigned int i = 0; i < vertices; i++)
    {
        for (unsigned int j = 0; j < vertices; j++)
        {
            cout << matrix[i][j] << "    ";
        }
        cout << "\n" << endl;
    }
}
