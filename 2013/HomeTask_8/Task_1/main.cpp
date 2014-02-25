#include <iostream>
#include <fstream>

using namespace std;

bool getInFileInformation(ifstream &infile);

void printQueue(unsigned int* queue, unsigned int vertices);
void printMatrix(unsigned int** matrix, unsigned int vertices);
void crab(unsigned int **matrix, const unsigned int vertices, unsigned int *&queue, const unsigned int current, char& letter);

int main()
{
    //!!____SETTING_STREAM_____
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    //!!_______________________
    unsigned int vertices = 0;
    infile >> vertices;
    cout << "number of vertices: " << vertices;

    unsigned int** matrix = new unsigned int* [vertices];
    for (unsigned int i = 0; i < vertices; i++)
    {
        matrix[i] = new unsigned int [vertices];
    }

    for (unsigned int i = 0; i < vertices; i++)
    {
        for (unsigned int j = 0; j < vertices; j++)
        {
            infile >> matrix[i][j];
        }
    }
    cout << "\nadjacency matrix of size " << vertices << "X" << vertices << endl;

    cout << endl;
    printMatrix(matrix, vertices);

    int start = 0;
    infile >> start;
    cout << "starting with element: " << start;
    cout << endl;
//!!
    unsigned int* queue = new unsigned int [vertices];
    for (unsigned int i = 0; i < vertices; i++)
    {
        queue[i] = true;
    }

    cout << endl;

    cout << "started crab()" << endl;
    char letter = 'a';
    crab(matrix, vertices, queue, start, letter);

    printMatrix(matrix, vertices);

    delete[] queue;
    for (unsigned int i = 0; i < vertices; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    //!!____CLOSING_STREAM_____
    infile.close();
    //!!_______________________
    return 0;
}

void crab(unsigned int** matrix, const unsigned int vertices, unsigned int*& queue, const unsigned int current, char& letter)
{
    unsigned int mod = current % vertices;
    if (queue[mod])
    {
        matrix[mod][mod] = letter;
        queue[mod] = false;
    }
    for (unsigned int j = 0; j < vertices; j++)
    {
        if ((matrix[mod][j]) && (queue[j]))
        {
            letter++;
            crab(matrix, vertices, queue, j, letter);
        }
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

void printQueue(unsigned int* queue, unsigned int vertices)
{
    cout << endl;
    cout << "queue(debug): ";
    for (unsigned int i = 0; i < vertices; i++)
    {
        cout<< queue[i] << " ";
    }
}

void printMatrix(unsigned int** matrix, unsigned int vertices)
{
    cout << "matrix(debug output)" << endl;
    for (unsigned int i = 0; i < vertices; i++)
    {
        for (unsigned int j = 0; j < vertices; j++)
        {
            cout << (char)(matrix[i][j] + ((matrix[i][j] <= 1)? '0' : 0)) << "    ";
        }
        cout << "\n" << endl;
    }
}
