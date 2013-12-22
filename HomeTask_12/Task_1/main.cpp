#include <iostream>
#include "doubleanal.h"

using namespace std;

bool isArifmExpression(char*& str);

bool isCompositionSign(char ch)
{
    return ch == '*' || ch == '/';
}

bool isCompositionToken(char*& str)
{
    if (isNumberWithFloatPoint(str) || ((*str == '(') && isArifmExpression(++str) && (*str == ')')))
    {
        return true;
    }
    return false;
}

bool isComposition(char*& str)
{
    if (!isCompositionSign(*str) || (isCompositionToken(++str) && isComposition(str)))
    {
        return true;
    }
    return false;
}

bool isSummToken(char*& str)
{
    if (isCompositionToken(str) && isComposition(str))
    {
        return true;
    }
    return false;
}

bool isSumm(char*& str)
{
    if (!isSign(*str) || (isSummToken(++str) && isSumm(str)))
    {
        return true;
    }
    return false;
}

bool isArifmExpression(char*& str)
{
    if (isSummToken(str) && isSumm(str))
    {
        return true;
    }
    return false;
}

int main()
{
    cout << "Checking arifmetical expression by this scheme(ε - empty string): \n\n";
    cout << "ArifmExpression  -> SummToken Summ\n";
    cout << "Summ             -> (+|-) SummToken Summ | ε\n";
    cout << "SummToken        -> CompositionToken Composition\n";
    cout << "Composition      -> (*|/) CompositionToken Composition | ε\n";
    cout << "CompositionToken -> (ArifmExpression) | NumberWithFloatPoint\n\n";
    cout << "Write expression: ";
    char* str = new char [500];
    cin.getline(str, 500);
    cout << ((isArifmExpression(str) && !*str) ? "\nIt is correct arifmetical expression" : "\nIt is NOT correct arifmetical expression");
    delete [] str;
    return 0;
}

