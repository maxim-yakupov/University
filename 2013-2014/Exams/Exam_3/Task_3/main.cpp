#include <iostream>

using namespace std;

bool isLowerCase(char ch)
{
    return ((ch >= 'a') && (ch <= 'z'));
}

bool isUpperCase(char ch)
{
    return ((ch >= 'A') && (ch <= 'Z'));
}

bool isDigit(char ch)
{
    return (ch >= '0') && (ch <= '9');
}

bool isEnd(char ch)
{
    return ch == '\0';
}

bool isCorrectString(char* str)
{
    enum states {BEG_STR, ANY_SMALL_LETTERS_BEG, ONE_BIG_LETTER, ANY_BIG_LETTERS, ONE_SMALL_LETTER, ONE_DIGIT, ANY_DIGITS, ANY_SMALL_LETTERS};
    states state = BEG_STR;
    while (true)
    {
        switch (state)
        {
        case BEG_STR:
            if (isLowerCase(str[0]))
            {
                state = ANY_SMALL_LETTERS_BEG;
                str++;
            }
            else
            {
                cout << "\n!!!STR_FIRST_SYMBOL_ERROR!!!\n";
                return false;
            }
            break;
        case ANY_SMALL_LETTERS_BEG:
            if (isLowerCase(str[0]))
            {
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else if (isUpperCase(str[0]))
            {
                state = ONE_BIG_LETTER;
            }
            else
            {
                cout << "\n!!!STR_BEGINNING_ERROR!!!\n";
                return false;
            }
            break;
        case ONE_BIG_LETTER:
            if (isUpperCase(str[0]))
            {
                state = ANY_BIG_LETTERS;
                str++;
            }
            else
            {
                cout << "\n!!!ONE_BIG_LETTER_ERROR!!!\n";
                return false;
            }
            break;
        case ANY_BIG_LETTERS:
            if (isUpperCase(str[0]))
            {
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else if (isLowerCase(str[0]))
            {
                state = ONE_SMALL_LETTER;
            }
            else if (isDigit(str[0]))
            {
                state = ONE_DIGIT;
            }
            else
            {
                cout << "\n!!!BIG_LETTERS_ENDING_ERROR!!!\n";
                return false;
            }
            break;
        case ONE_SMALL_LETTER:
            if (isLowerCase(str[0]))
            {
                state = ANY_SMALL_LETTERS;
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else
            {
                cout << "\n!!!ONE_SMALL_LETTER_ERROR!!!\n";
                return false;
            }
            break;
        case ONE_DIGIT:
            if (isDigit(str[0]))
            {
                state = ANY_DIGITS;
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else
            {
                cout << "\n!!!ONE_DIGIT_ERROR!!!\n";
                return false;
            }
            break;
        case ANY_SMALL_LETTERS:
            if (isLowerCase(str[0]))
            {
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else if (isUpperCase(str[0]))
            {
                state = ONE_BIG_LETTER;
            }
            else
            {
                cout << "\n!!!ANY_SMALL_LETTERS_ENDING_ERROR!!!\n";
                return false;
            }
            break;
        case ANY_DIGITS:
            if (isDigit(str[0]))
            {
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else if (isUpperCase(str[0]))
            {
                state = ONE_BIG_LETTER;
            }
            else
            {
                cout << "\n!!!ANY_DIGITS_ENDING_ERROR!!!\n";
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
    cout << "[a..z]([A..Z]([a..z] | [0..9])*)*\n";
    cout << "Write string: ";
    char* str = new char [500];
    cin.getline(str, 500);
    cout << (isCorrectString(str) ? "\nIt is a correct string" : "\nIt is NOT a correct string");
    delete [] str;
    return 0;
}
