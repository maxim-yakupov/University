#include <iostream>
#include <fstream>

/*
 *Yakupov Maxim (c)
 */

using namespace std;

bool getInFileInformation(ifstream &infile);
bool openOutFile(fstream &outfile);

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }

    fstream out;
    cout << (openOutFile(out) ? "Result in file 'output.txt'" : "Was created file 'output.txt'");

    const unsigned int lineSize = 1000;

    unsigned int counter[256];
    for (int i = 0; i < 256; i++)
    {
        counter[i] = 0;
    }

    do
    {
        char* currentLine = new char[lineSize];
        infile.getline(currentLine, lineSize);
        char* currentChar = currentLine;
        while (currentChar[0])
        {
            if ((currentChar[0] >= 'a') && (currentChar[0] <= 'z'))
            {
                counter[(unsigned int) currentChar[0]]++;
            }
            currentChar++;
        }
        delete [] currentLine;
    } while(!infile.eof());

    for (char i = 'a'; i <= 'z'; i++)
    {
        if (counter[(unsigned int) i])
        {
            out << i << " -- " << counter[(unsigned int) i] << "\n";
        }
    }

    out.close();
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

bool openOutFile(fstream &outfile)
{
    outfile.open("output.txt", ios_base::trunc);
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
