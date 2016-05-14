#include "stdio.h"
#include <cstring>

void readLine(char str[]);
int typeOfBracket(char ch);

int main()
{
    const int maxLengthOfStr = 50;
    char str[maxLengthOfStr] = {'\0'};
    printf("Write your string: ");
    readLine(str);
    if (strlen(str) != 0)
    {
        printf("\nBalance of the brackets is WRONG!");
    }
    else
    {
        printf("\nBalance of the brackets is right");
    };
    return 0;
}

void readLine(char str[])
{
    while (scanf("%c", &str[strlen(str)]))
    {
        int typeOfLastBr = typeOfBracket(str[strlen(str) - 1]);

        if (typeOfLastBr != 0)
        {
            if (typeOfLastBr > 3)
            {
                if (strlen(str) == 1)
                {
                    break;
                }
                else
                {
                    int typeOfPrevBr = typeOfBracket(str[strlen(str) - 2]);

                    if (typeOfLastBr - typeOfPrevBr == 3)
                    {
                        str[strlen(str) - 1] = '\0';
                        str[strlen(str) - 1] = '\0';
                    }
                    else
                    {
                        break;
                    };
                };
            };
        }
        else
        {
            char check = str[strlen(str) - 1];
            str[strlen(str) - 1] = '\0';
            if ((check == '\n') || (check == '\r'))
            {
                break;
            }
            else
            {
                continue;
            };
        };
    };
}

int typeOfBracket(char ch)
{
    int i = 0;
    char arrayOfBrackets[6] = {'(','[','{',')',']','}'};
    for (i = 0; i <= 5; i++)
    {
        if (ch == arrayOfBrackets[i])
        {
            return i + 1;
            break;
        };
    };
    if (i == 6)
    {
        return 0;
    };
}
