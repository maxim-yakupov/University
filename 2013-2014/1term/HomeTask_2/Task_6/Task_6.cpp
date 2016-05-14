#include "stdio.h"
#include <cstring> //для работы strlen()

using namespace std;

const int maxLength = 10;
const int maxAmountOfParams = 20;
const int outputLength = maxAmountOfParams * (maxLength + 3);

int readLine(char str[maxAmountOfParams][maxLength]);
void insertBigDegree(char fLine[], char sLine[], int degree);
void clearExtraMembers(char fStr[outputLength], char sStr[outputLength]);

int main()
{
    printf("Write parameters(first parameter can't be zero!)[amount of parameters <= %d ]:\n", maxAmountOfParams);
    char parameters[maxAmountOfParams][maxLength] = {'\0'};
    int numberOfParams = readLine(parameters) + 1;
    char firstLine[outputLength] = {'\0'};//достаточно длинная строка
    char secondLine[outputLength] = {'\0'};//достаточно длинная строка
    int currentDegree = numberOfParams - 1;
    for (int i = 0; i < numberOfParams; i++)
    {
        for (unsigned int j = 0; j < strlen(parameters[i]); j++)
        {
            firstLine[strlen(firstLine)] = ' ';
            secondLine[strlen(secondLine)] = parameters[i][j];
        };
        if (currentDegree > 1)
        {
            firstLine[strlen(firstLine)] = ' ';
            secondLine[strlen(secondLine)] = 'x';
            insertBigDegree(firstLine, secondLine, currentDegree);
        }
        else if (currentDegree == 1)
        {
            firstLine[strlen(firstLine)] = ' ';
            secondLine[strlen(secondLine)] = 'x';
        };
        currentDegree--;
    };
    clearExtraMembers(firstLine, secondLine);
    printf("%s\n", firstLine);
    printf("%s\n", secondLine);

    return 0;
}

void delOne(char str[maxAmountOfParams][maxLength], int counter)
{
    if ((str[counter][0] == '1') && (strlen(str[counter]) == 1))
    {
        str[counter][0] = '\0';
    }
    else if ((str[counter][0] == '-') && (str[counter][1] == '1') && (strlen(str[counter]) == 2))
    {
        str[counter][1] = '\0';
    };
}

void addPlus(char str[maxAmountOfParams][maxLength], int numberOfParam)
{
    if (str[numberOfParam][0] != '-')
    {
        for (int j = strlen(str[numberOfParam]); j > 0; j--)
        {
            str[numberOfParam][j] = str[numberOfParam][j - 1];
        };
        str[numberOfParam][0] = '+';
    };
}

int readLine(char str[maxAmountOfParams][maxLength])
{
    int counter = 0;
    scanf("%s", &str[counter][strlen(str[counter])]);
    delOne(str, counter);
    while (scanf("%c", &str[counter][strlen(str[counter])]))
    {
        if (str[counter][strlen(str[counter]) - 1] == ' ')
        {
            str[counter][strlen(str[counter]) - 1] = '\0';
            counter++;
            scanf("%s", &str[counter][strlen(str[counter])]);
            delOne(str, counter);
            addPlus(str, counter);
        }
        else
        {
            str[counter][strlen(str[counter]) - 1] = '\0';
            break;
        };
    };
    return counter;
}

void insertBigDegree(char fLine[], char sLine[], int degree)
{
    char strDegree[maxLength] = {'\0'};
    while (degree != 0)
    {
        strDegree[strlen(strDegree)] = degree % 10 + '0';
        degree /= 10;
    };
    const int lengthOfDegree = strlen(strDegree);
    for (int i = lengthOfDegree - 1; i >= 0; i--)
    {
        fLine[strlen(fLine)] = strDegree[i];
        sLine[strlen(sLine)] = ' ';
    };
}

void rToLeftShift(char fStr[outputLength], char sStr[outputLength], int pos, int delta)
{
    const int lengthOfStr = strlen(fStr);
    for (int i = pos; i <= pos + delta; i++)
    {
        fStr[i] = ' ';
    };
    while (sStr[pos + delta] == ' ')
    {
        delta++;
    };
    for (int i = pos; i < lengthOfStr; i++)
    {
        fStr[i] = fStr[i + delta];
        sStr[i] = sStr[i + delta];
    };

}

void clearExtraMembers(char fStr[outputLength], char sStr[outputLength])
{
    if (strlen(sStr) != 1)
    {
        unsigned int i = 1;
        while (i < strlen(sStr) - 2)
        {
            int shift = 0;
            if (((sStr[i - 1] == '-') || (sStr[i - 1] == '+')) && (sStr[i] == '0') && (sStr[i + 1] == 'x'))
            {
                shift = 3;
                if (sStr[i + 2] == ' ')
                {
                    shift++;
                };
            };
            if (shift != 0)
            {
                rToLeftShift(fStr, sStr, i - 1, shift);
            }
            else
            {
                i++;
            };
        };
    };
    const int lengthOfStr = strlen(sStr);
    if ((sStr[lengthOfStr - 1] == '-') || (sStr[lengthOfStr - 1] == '+'))
    {
        sStr[lengthOfStr] = '1';
    };
}
