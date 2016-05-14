#include <iostream>
#include <fstream>

using namespace std;

bool getInFileInformation(ifstream &infile);

int main()
{
    setlocale (LC_ALL, "RUS");
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }

    bool isOpenMultiStringComment = false;
    bool isOpenTextArea = false;
    char current = '\0';
    while (!infile.eof())
    {
        bool isPrevStarChar = (current == '*');
        current = infile.get();
        if (current == '/')
        {
            if (isPrevStarChar)
            {
                isOpenMultiStringComment = false;
            }

            if (((current = infile.get()) == '*') && (!isPrevStarChar || !isOpenMultiStringComment))
            {
                isOpenMultiStringComment = true;
                current = infile.get();
            }
            else if ((current == '/') && (!isOpenMultiStringComment) && (!isOpenTextArea))
            {
                cout << "//";
                while (((current = infile.get()) != '\n') && (!infile.eof()))
                {
                    cout << current;
                }
                cout << '\n';
            }
        }
        else if (current == '"')
        {
            isOpenTextArea = !isOpenTextArea;
        }
    }
    cout << "=====End  of output=====";

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
    cout << "===Begining of output===" << endl;
    return 0;
}
