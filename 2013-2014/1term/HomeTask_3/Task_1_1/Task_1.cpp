#include "stdio.h"

using namespace std;

int strlen(char* str);

int main()
{
    const int amountOfPossibleValuesOfChar = 128;
    printf("Write first string:  ");
    char* fStr = new char[100] {'\0'};
    scanf("%s", fStr);
    printf("Write second string: ");
    char* sStr = new char[100] {'\0'};
    scanf("%s", sStr);

    int fLength = strlen(fStr);
    int sLength = strlen(sStr);

    bool answer = false;
    if (fLength == sLength)
    {
        int* counterOfMatches = new int[amountOfPossibleValuesOfChar];
        for (int i = 0; i < amountOfPossibleValuesOfChar; i++)
        {
            counterOfMatches[i] = 0;
        };
        for (int i = 0; i < fLength; i++)
        {
            counterOfMatches[fStr[i]]++;
            counterOfMatches[sStr[i]]--;
        };
        answer = true;
        for (int i = 0; i < amountOfPossibleValuesOfChar; i++)
        {
            if (counterOfMatches[i] != 0)
            {
                answer = false;
                break;
            };
        };
        delete [] counterOfMatches;
    };

    if (answer)
    {
        printf("Yes, you can get second string from first string due to permutations");
    }
    else
    {
        printf("No, you can't get second string from first string due to permutations");
    };
    delete [] fStr;
    delete [] sStr;
    return 0;
}

int strlen(char* str)
{
    int length = 0;
    while (*(str + length) != '\0')
    {
        length++;
    };
    return length;
}
