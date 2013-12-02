#include <iostream>
#include <fstream>
#include "maxstring.h"

using namespace std;
using namespace stringAPI;

bool getInFileInformation(ifstream &infile);
bool openOutFile(fstream &outfile);

int main()
{
    //!!____SETTING_STREAMs____
    ifstream infile1;
    if (getInFileInformation(infile1))
    {
        return 0;
    }
    ifstream infile2;
    if (getInFileInformation(infile2))
    {
        return 0;
    }
    fstream out;
    cout << (openOutFile(out) ? "Result in file 'output.txt'" : "Was created file 'output.txt'");
    //!!_______________________

    //!!____CLOSING_STREAMs____
    infile1.close();
    infile2.close();
    out.close();
    //!!_______________________
    return 0;
}

void refreshCString(char*& s)
{
    delete[] s;
    s = new char[maxStringLength];
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

bool openOutFile(fstream &outfile)
{
    outfile.open("output.txt");
    if (!outfile.is_open())//if don't exists
    {
        outfile.open("output.txt", ios_base::in | ios_base::out | ios_base::trunc);//create
        return false;
    }
    else
    {
        return true;
    }
}

void readStringsBase(ifstream &infile, StringsBase* base)
{
    char* inChar;
    refreshCString(inChar);
    while (!phoneBase.eof())
    {
        infile.getline(inChar, 500);
        if (inChar[0] != '\0')
        {
            addRecord(name, phone, phonebook);
        }
        else
        {
            delete [] record;
        }
        refreshCString(inChar);
    }
}
