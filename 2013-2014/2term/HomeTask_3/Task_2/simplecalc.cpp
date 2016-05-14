#include "simplecalc.h"

int SimpleCalc::compute(int result, int secondField, int operation)
{
    if (operation == 0)
    {
        result += secondField;
    }
    else if (operation == 1)
    {
        result -= secondField;
    }
    else if (operation == 2)
    {
        result *= secondField;
    }
    else if (operation == 3)
    {
        result /= secondField;
    }
    else if (operation == 4)
    {
        result %= secondField;
    }
    return result;
}
