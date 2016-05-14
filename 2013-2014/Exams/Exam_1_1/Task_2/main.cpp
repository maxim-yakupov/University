#include <iostream>

using namespace std;

bool isNotALetterOrNumber(char ch)
{
    return (!(((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || ((ch >= '0') && (ch <= '9'))));
}

int main()
{
    char* input = new char[999] {'\0'};
    char* words[999] = {'\0'};
    int amountOfWords = 0;
    int i = 0;
    int length = 0;
    cout << "Write words, separeted by [Space] end type [Enter]: ";
    input[i] = cin.get();
    while (true)
    {
        input[i + 1] = '\0';
        if (isNotALetterOrNumber(input[i]))
        {
            bool fl =(input[i] == '\n') || (input[i] == '\r');
            input[i] = '\0';
            words[amountOfWords] = input;
            amountOfWords++;
            i = -1;
            input = new char[999] {'\0'};
            if (fl)
            {
                break;
            }
        }
        else
        {
            length++;
        }
        i++;
        input[i] = cin.get();
    }
    cout << "Write number of chars in result string: ";
    int resultLength = 0;
    cin >> resultLength;
    int amountOfSpaces = resultLength - length;
    cout << endl;
    cout << "Result:";
    int garantedSpaces = amountOfSpaces / (amountOfWords - 1);
    amountOfSpaces = amountOfSpaces % (amountOfWords - 1);
    for (int i = 0; i < amountOfWords; i++)
    {
        cout << words[i];
        if (i != amountOfWords - 1)
        {
            for (int j = 0; j < garantedSpaces; j++)
            {
                cout << " ";
            }
        }

        if (amountOfSpaces > 0)
        {
            cout << " ";
            amountOfSpaces--;
        }
    }
    for (int i = 0; i < amountOfWords; i++)
    {
        delete [] words[i];
    }
    delete [] input;
    return 0;
}

