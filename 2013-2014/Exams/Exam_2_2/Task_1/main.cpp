#include <iostream>
#include <fstream>
#include "maxstring.h"

using namespace std;
using namespace stringAPI;

bool getInFileInformation(ifstream &infile);

void solve(String *strs);

const unsigned int strMaxLength = 500;

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    String strs[2];

    char* read = new char[strMaxLength];
    infile.getline(read, strMaxLength);
    strs[0] = createString(read);
    delete [] read;

    read = new char[strMaxLength];
    infile.getline(read, strMaxLength);
    strs[1] = createString(read);
    delete [] read;

    solve(strs);

    deleteString(strs[0]);
    deleteString(strs[1]);
    infile.close();
    return 0;
}

void printOut(int fl)
{
    if (fl > 1)
    {
        cout << "Are equal";
    }
    else if (fl == 0)
    {
        cout << "First more, than second";
    }
    else
    {
        cout << "First less, than second";
    }
}

void solve(String *strs)
{
    String prefix = createString();

    int mostLength = 0;

    if (strs[0].length != strs[1].length)
    {
        if (strs[0].length < strs[1].length)
        {
            prefix = subString(strs[1], 0, strs[1].length - strs[0].length);
            changeString(strs[1], strs[1].beginning + strs[1].length - strs[0].length);
            mostLength = 1;
        }
        else
        {
            prefix = subString(strs[0], 0, strs[0].length - strs[1].length);
            changeString(strs[0], strs[0].beginning + strs[0].length - strs[1].length);
        }

        int counter = 0;

        do
        {
            if (prefix.beginning[counter] != '0')
            {
                deleteString(prefix);
                printOut(mostLength);
                return;
            }
            counter++;
        }
        while (counter != prefix.length);
        deleteString(prefix);
    }

    if (areEqualStrings(strs[0], strs[1]))
    {
        printOut(2);
        return;
    }

    mostLength = 0;

    int counter = 0;

    while (counter != strs[0].length)
    {
        if (strs[0].beginning[counter] != strs[1].beginning[counter])
        {
            if (strs[1].beginning[counter] == '1')
            {
                mostLength = 1;
            }
            break;
        }
        counter++;
    }

    printOut(mostLength);
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
