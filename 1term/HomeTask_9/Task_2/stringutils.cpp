#include "stringutils.h"

int charStringLength(const char str[])
{
    int counter = 0;
    while (str[counter] != '\0')
    {
        counter++;
    }
    return counter;
}

bool compare(char* str1, char* str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return !*str1;
}
