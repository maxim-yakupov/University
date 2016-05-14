#include <iostream>
#include <fstream>

using namespace std;

bool getInFileInformation(ifstream &infile);
int strlen(char* str);

int main()
{
    setlocale (LC_ALL, "RUS");
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }

    char word[100] = {'\0'};
    while (!infile.eof())
    {
        infile >> word;
        int length = strlen(word);
        if (length == 0)
        {
            continue;
        }
        cout << word[0];
        int counter = 1;
        while (length != counter)
        {
            int i = counter - 1;
            while (-1 != i)
            {
                if (word[counter] == word[i])
                {
                    break;
                }
                else
                {
                    i--;
                }
            }
            if (i == -1)
            {
                cout << word[counter];
            }
            counter++;
        }
        cout << endl;
    }

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
    cout << "==========" << endl;
    return 0;
}

int strlen(char* str)
{
    int length = 0;
    while (*(str + length) != '\0')
    {
        length++;
    }
    return length;
}
