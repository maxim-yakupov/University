#include <iostream>
#include <fstream>

/*
 *Yakupov Maxim (c)
 */

using namespace std;

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

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }

    const unsigned int lineSize = 1000;

    unsigned int counter = 0;
    do
    {
        char* currentLine = new char[lineSize];
        infile.getline(currentLine, lineSize);
        char* currentChar = currentLine;
        counter++;
        while (currentChar[0])
        {
            if ((currentChar[0] != ' ') && (currentChar[0] != '\t'))
            {
                counter--;
                break;
            }
            currentChar++;
        }
        delete [] currentLine;
    } while(!infile.eof());

    cout << "Number of empty strings in file: " << counter;
    infile.close();
    return 0;
}

