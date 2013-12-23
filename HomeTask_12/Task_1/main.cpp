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
    return (isNumberWithFloatPoint(str) || ((*str == '(') && isArifmExpression(++str) && (*(str++) == ')')));
}

bool isComposition(char*& str)
{
    return (!isCompositionSign(*str) || (isCompositionToken(++str) && isComposition(str)));
}

bool isSummToken(char*& str)
{
    return (isCompositionToken(str) && isComposition(str));
}

bool isSumm(char*& str)
{
    return (!isSign(*str) || (isSummToken(++str) && isSumm(str)));
}

bool isArifmExpression(char*& str)
{
    return (isSummToken(str) && isSumm(str));
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
    char* stream = str;
    cin.getline(str, 500);
    cout << ((isArifmExpression(stream) && !*stream) ? "\nIt is correct arifmetical expression" : "\nIt is NOT correct arifmetical expression");
    delete [] str;
    return 0;
}

