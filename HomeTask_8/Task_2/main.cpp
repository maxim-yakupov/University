#include <iostream>
#include <fstream>
#include <climits>

/*
 *
 * Numeration of cities in input file begins with 0 (zero)
 *
 */

using namespace std;

struct Node
{
    int parent;
    int lengthOfPath;
};

unsigned int getNextInQueue(Node* pathMatrix, unsigned int*& queue, const unsigned int vertices);
void cleanUpQueue(unsigned int* queue, const unsigned int vertices);
void cleanUpPathMatrix(Node* pathMatrix, const unsigned int vertices, unsigned int start);
bool getInFileInformation(ifstream &infile);
void printMatrix(unsigned int** matrix, unsigned int vertices);
bool isQueueEmpty(unsigned int*& queue, const unsigned int vertices);
void dijkstra(unsigned int** matrix, Node* pathMatrix, const unsigned int vertices, unsigned int*& queue, const unsigned int current);

int main()
{
    //!!____SETTING_STREAM_____
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    //!!_______________________
    //!!_GETTING&PRINTING_INFORMATION_
    unsigned int vertices = 0;
    infile >> vertices;
    cout << "number of vertices: " << vertices;

    unsigned int roads = 0;
    infile >> roads;

    unsigned int** matrix = new unsigned int* [vertices];
    for (unsigned int i = 0; i < vertices; i++)
    {
        matrix[i] = new unsigned int [vertices];
        for (unsigned int j = 0; j < vertices; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (unsigned int i = 0; i < roads; i++)
    {
        int x , y, len = 0;
        infile >> x >> y >> len;
        matrix[x][y] = len;
        matrix[y][x] = len;
    }
    cout << "\nadjacency matrix of size " << vertices << "X" << vertices << endl;

    cout << endl;
    printMatrix(matrix, vertices);
    //!!______________________________
    //!!INITIALISATION_OF_ENVIRONMENT
    unsigned int* printQueue = new unsigned int [vertices];
    unsigned int* pathQueue = new unsigned int [vertices];
    Node* pathMatrix = new Node [vertices];

    cleanUpQueue(printQueue, vertices);
    cleanUpPathMatrix(pathMatrix, vertices, 4);

    cout << endl;

    unsigned int next = 0;
    unsigned int current = 0;
    unsigned int summaryPath = 0;
    //!!_____________________________
    //!!________THE_MAIN_LOOP________
    while (!isQueueEmpty(printQueue, vertices))
    {
        current = getNextInQueue(pathMatrix, printQueue, vertices);
        cleanUpPathMatrix(pathMatrix, vertices, current);
        cleanUpQueue(pathQueue, vertices);
        if (current)
        {
            cout << "   to ";
        }
        else
        {
            cout << "first ";
        }
        cout << "town: " << current << " length of path between first & current: " << summaryPath;
        printQueue[current] = false;
        dijkstra(matrix, pathMatrix, vertices, pathQueue, current);
        next = getNextInQueue(pathMatrix, printQueue, vertices);
        summaryPath += pathMatrix[next].lengthOfPath;
        //!!TRANSITIONAL_VERTICES
        if (pathMatrix[next].parent != current)
        {
            cout << "\n      went through";
            for (int i = pathMatrix[next].parent; i != current; i = pathMatrix[i].parent)
            {
                cout << " " << i;
            }
        }
        //!!_____________________
        cout << endl;
    }
    //!!_____________________________
    //!!____FREE MEMORY_____
    delete[] printQueue;
    delete[] pathQueue;

    for (unsigned int i = 0; i < vertices; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    delete[] pathMatrix;
    //!!_______________________
    //!!____CLOSING_STREAM_____
    infile.close();
    //!!_______________________
    return 0;
}

void cleanUpQueue(unsigned int* queue, const unsigned int vertices)
{
    for (unsigned int i = 0; i < vertices; i++)
    {
        queue[i] = true;
    }
}

void cleanUpPathMatrix(Node* pathMatrix, const unsigned int vertices, unsigned int start)
{
    for (unsigned int i = 0; i < vertices; i++)
    {
        pathMatrix[i].parent = -1;
        pathMatrix[i].lengthOfPath = -1;
    }
    if (start < vertices)
    {
        pathMatrix[start].lengthOfPath = 0;
    }
}

int fromInfToNum(int num)
{
    if (num > -1)
    {
        return num;
    }
    else
    {
        return INT_MAX;
    }
}

bool isQueueEmpty(unsigned int*& queue, const unsigned int vertices)
{
    for (unsigned int i = 0; i < vertices; i++)
    {
        if (queue[i])
        {
            return false;
        }
    }
    return true;
}

unsigned int getNextInQueue(Node* pathMatrix, unsigned int*& queue, const unsigned int vertices)
{
    unsigned int next = 0;
    for (unsigned int i = 0; i < vertices; i++)
    {
        if ((queue[i]) && ((fromInfToNum(pathMatrix[i].lengthOfPath) < fromInfToNum(pathMatrix[next].lengthOfPath)) || fromInfToNum(pathMatrix[next].lengthOfPath) == 0))
        {
            next = i;
        }
    }
    return next;
}

void dijkstra(unsigned int** matrix, Node* pathMatrix, const unsigned int vertices, unsigned int*& queue, const unsigned int current)
{
    if (queue[current])
    {
        for (unsigned int i = 0; i < vertices; i++)
        {
            if ((queue[i]) && (matrix[current][i]))
            {
                int calcNewPath = pathMatrix[current].lengthOfPath + matrix[current][i];
                if (fromInfToNum(pathMatrix[i].lengthOfPath) > calcNewPath)
                {
                    pathMatrix[i].lengthOfPath = calcNewPath;
                    pathMatrix[i].parent = current;
                }
            }
        }
        queue[current] = false;
        dijkstra(matrix, pathMatrix, vertices, queue, getNextInQueue(pathMatrix, queue, vertices));
    }
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
    cout << "matrix(debug output)" << endl;
    for (unsigned int i = 0; i < vertices; i++)
    {
        for (unsigned int j = 0; j < vertices; j++)
        {
            cout << matrix[i][j] << "    ";
        }
        cout << "\n" << endl;
    }
}
