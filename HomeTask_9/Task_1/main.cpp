#include <iostream>
#include <fstream>
#include "maxstring.h"

using namespace std;
using namespace stringAPI;

const int maxStringLength = 500;

bool getInFileInformation(ifstream &infile);
bool openOutFile(fstream &outfile);

struct ListElement
{
    String value;
    ListElement* next;
};

struct List
{
    ListElement* head;
};

void readStringsList(ifstream &infile, List &list);
void readAndCheck(ifstream &infile, List& list, fstream& out);

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

    List firstFile;
    firstFile.head = nullptr;
    readStringsList(infile1, firstFile);
    readAndCheck(infile2, firstFile, out);

    ListElement* buff = nullptr;
    while (firstFile.head)
    {
        buff = firstFile.head->next;
        deleteString(firstFile.head->value);
        delete firstFile.head;
        firstFile.head = buff;
    }
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

void readStringsList(ifstream &infile, List& list)
{
    char* inChar;
    refreshCString(inChar);
    while (!infile.eof())
    {
        infile.getline(inChar, 500);
        list.head = new ListElement{createString(inChar), list.head};
        refreshCString(inChar);
    }
}

void readAndCheck(ifstream &infile, List& list, fstream &out)
{
    cout << "\n===Output===";
    char* inChar;
    refreshCString(inChar);
    String input = createString();
    while (!infile.eof())
    {
        infile.getline(inChar, 500);
        changeString(input, inChar);
        ListElement* current = list.head;
        while (current)
        {
            if (areEqualStrings(current->value, input))
            {
                cout << "\n" << stringToCharPtr(input);
                out << stringToCharPtr(input) << endl;
                break;
            }
            current = current->next;
        }
        refreshCString(inChar);
    }
    deleteString(input);
}
