#include <iostream>

using namespace std;

bool isUpperCase(char ch)
{
    return ((ch >= 'A') && (ch <= 'Z'));
}

bool isDigit(char ch)
{
    return (ch >= '0') && (ch <= '9');
}

bool isSymbol(char ch)
{
    return ((ch == '.') || (ch == '_') || (ch == '%') || (ch == '+') || (ch == '-'));
}

bool isEnd(char ch)
{
    return ch == '\0';
}
//[A-Z0-9._%+-]+@([A-Z0-9-]+\.)+[A-Z]
bool isCorrectString(char* str)
{
    enum States
    {
        oneFromFirstBracers,
        anyFromFirstBracers,
        oneSecondBracers,
        anyFromInnerBracers,
        anySecondBracers
    };
    States state = oneFromFirstBracers;
    while (true)
    {
        switch (state)
        {
        case oneFromFirstBracers://[A-Z0-9._%+-]
            if (isUpperCase(*str) || isDigit(*str) || isSymbol(*str))
            {
                state = anyFromFirstBracers;
                str++;
            }
            else
            {
                cout << "\n!!!_1_!!!\n";
                return false;
            }
            break;
        case anyFromFirstBracers:
            if (isUpperCase(*str) || isDigit(*str) || isSymbol(*str))
            {
                str++;
            }
            else if (*str == '@')
            {
                state = oneSecondBracers;
                str++;
            }
            else
            {
                cout << "\n!!!_2_!!!\n";
                return false;
            }
            break;
        case oneSecondBracers://([A-Z0-9-]+\.)
            if (isUpperCase(*str) || isDigit(*str) || (*str == '-'))
            {
                state = anyFromInnerBracers;
                str++;
            }
            else
            {
                cout << "\n!!!_3_!!!\n";
                return false;
            }
            break;
        case anyFromInnerBracers://[A-Z0-9-]
            if (isUpperCase(*str) || isDigit(*str) || (*str == '-'))
            {
                str++;
            }
            else if (*str == '.')
            {
                state = anySecondBracers;
                str++;
            }
            else
            {
                cout << "\n!!!_4_!!!\n";
                return false;
            }
            break;
        case anySecondBracers://([A-Z0-9-]+\.)*
            if (isUpperCase(*str) && isEnd(str[1]))
            {
                return true;
            }
            else if (isUpperCase(*str) || isDigit(*str) || (*str == '-'))
            {
                state = anyFromInnerBracers;
                str++;
            }
            else
            {
                cout << "\n!!!_5_!!!\n";
                return false;
            }
            break;
        default://strange situation
            cout << "\n!!!STRANGE_ERROR!!!\n";
            break;
        }
    }
}

int main()
{
    cout << "Checking string by this regular expression: \n";
    cout << "[A-Z0-9._%+-]+@([A-Z0-9-]+\.)+[A-Z]\n";
    cout << "Write string: ";
    char* str = new char [500];
    cin.getline(str, 500);
    cout << (isCorrectString(str) ? "\nIt is a correct string" : "\nIt is NOT a correct string");
    delete [] str;
    return 0;
}

