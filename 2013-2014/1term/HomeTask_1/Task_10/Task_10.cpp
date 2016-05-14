#include "stdio.h"
#include <cstring> //для работы strlen()
//извините, но это нужно, чтобы можно было считать строку с пробелами с помощью scanf
//то, что вы мне написали ни в каком виде не работает,
//либо работает, но считывает до первого пробела :(
//------
//UPD: в stdio.h нет функции, которая возвращает длину строки, поэтому оставляю <cstring>
//using namespace std;

void readLine(char str[]);

int main()
{
    const int maxLengthOfStr = 50;
    char str[maxLengthOfStr] = {'\0'};

    printf("Enter your string: ");
    readLine(str);
    printf("\n");

    const int lengthOfStr = strlen(str);

    bool fl = true;

    for (int i = 0; i <= (lengthOfStr / 2 - 1); i++)
    {
        if (str[i] != str[lengthOfStr - i - 1])
        {
            fl = false;
            break;
        };
    };

    if (fl)
    {
        printf("It is palindom\n");
    }
    else
    {
        printf("It is NOT palindom\n");

    };
    return 0;
}

void readLine(char str[])
{
    scanf("%s", &str[strlen(str)]);
    while (scanf("%c", &str[strlen(str)]))
    {
        if (str[strlen(str) - 1] == ' ')
       {
            scanf("%s", &str[strlen(str)]);
       }
       else
       {
          str[strlen(str) - 1] = '\0';
           break;
       };
    };
}
