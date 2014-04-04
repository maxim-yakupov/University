#include <iostream>
#include <fstream>
#include "mathtree.h"

using namespace std;

bool getInFileInformation(ifstream &infile);

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }

    char* strExpr = new char[5000];
    infile.getline(strExpr, 5000);
    MathTree myTree(strExpr);

    cout << "=======================" << endl;
    myTree.print();
    cout << " = " << myTree.compute();

    infile.close();
    return 0;
}

bool getInFileInformation(ifstream &infile)
{
    cout << "Write file name(for input)[only utf-8 chars!]: ";
    char destination[100] = {'\0'};
    cin >> destination;
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
