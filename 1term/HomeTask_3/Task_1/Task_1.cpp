#include "stdio.h"

using namespace std;

int strlen(char* str);
void delCharFromStr(char &ch);

int main()
{
    printf("Write first string: ");
    char firstStr[100] = {'\0'};
    scanf("%s", firstStr);

    printf("Write second string: ");
    char secondStr[100] = {'\0'};
    scanf("%s", secondStr);

    int lengthFirst = strlen(firstStr);
    int lengthSecond = strlen(secondStr);

    bool answer = false;
    if (lengthFirst == lengthSecond)
    {
        for (int i = 0; i < lengthFirst; i++)
        {
            bool isCharMatched = false;
            for (int j = 0; j < strlen(secondStr); j++)
            {
                if (firstStr[i] == secondStr[j])
                {
                    isCharMatched = true;
                    answer = true;
                    delCharFromStr(secondStr[j]);
                    break;
                };
            };
            if (!isCharMatched)
            {
                answer = false;
                break;
            };
        };
    };
    if (answer)
    {
        printf("Yes, you can get second string from first string due to permutations");
    }
    else
    {
        printf("No, you can't get second string from first string due to permutations");
    };
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

void delCharFromStr(char &ch)
{
    int length = strlen(&ch);
    int pos = 0;
    while (pos < length)
    {
        *(&ch + pos) = *(&ch + pos + 1);
        pos++;
    };
}

