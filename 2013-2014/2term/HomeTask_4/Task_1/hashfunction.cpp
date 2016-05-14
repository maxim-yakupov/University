#include "hashfunction.h"

int HashFunction::hash(const char *str)
{
    int res = 0;
    for (int i = 0; str[i]; i++)
    {
        res = (res * 3 - 100 + str[i] - '0') % 5;
    };
    return res;
}
