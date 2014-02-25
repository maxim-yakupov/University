#include "stdio.h"
#include <cstring> //для работы strlen()

using namespace std;

int countEntries(char sub[], char str[]);
void readLine(char str[]);

int main()
{
    const int maxLengthOfStr = 50;
    char str[maxLengthOfStr] = {'\0'};
    char substr[maxLengthOfStr] = {'\0'};

    printf("Enter your string: ");
    readLine(str);
    printf("\n");

    printf("Enter your substring: ");
    readLine(substr);
    printf("\n");

    printf("Number of entries your substring in your string is %d", countEntries(substr, str));
    return 0;
}

int countEntries(char sub[], char str[])
{
    const int subLength = strlen(sub);
    const int strLength = strlen(str);
    int counter = 0;
    for (int i = subLength - 1; i <= strLength - 1; i++)
    {
        int pos = i;
        for (int j = i; j >= i - subLength + 1; j--)
        {
            if (str[j] != sub[subLength - 1 - i + j])
            {
                break;
            };
            pos--;
        };
        if (pos == i - subLength)
        {
            counter++;
        };
    };
    return counter;
}

void readLine(char str[])//усовершенствовал, теперь можно вводить строки с пробелом в конце
{
    scanf("%s", &str[strlen(str)]);
    while (scanf("%c", &str[strlen(str)]))
    {
        if (str[strlen(str) - 1] == ' ')
        {
            scanf("%c", &str[strlen(str)]);
            int lastChar = str[strlen(str) - 1];
            if ((lastChar == '\n')||(lastChar == '\r'))
            {
                str[strlen(str) - 1] = '\0';
                break;
            };
            scanf("%s", &str[strlen(str)]);
        }
        else
        {
            str[strlen(str) - 1] = '\0';
            break;
        };
    };
}
