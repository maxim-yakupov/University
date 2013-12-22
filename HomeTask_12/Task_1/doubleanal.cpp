#include "doubleanal.h"

bool isE(char ch)
{
    return ch == 'e' || ch == 'E';
}

bool isDigit(char ch)
{
    return (ch >= '0') && (ch <= '9');
}

bool isDot(char ch)
{
    return ch == '.';
}

bool isSign(char ch)
{
    return ch == '+' || ch == '-';
}

bool isEnd(char ch)
{
    return !(isE(ch) || isDigit(ch) || isDot(ch));
}

//(sign | ε) (dig) ((.) (dig) (dig*) | ε) ((e | E) (sign | ε) (dig) (dig*) | ε)

bool isNumberWithFloatPoint(char*& str)
{
    enum states {BEG_MANT, ONE_DIG_MANT, DOT_OR_E, ONE_DIG_AFTER_DOT, ANY_DIG_MANT, BEG_EXP, ONE_DIG_EXP, ANY_DIG_EXP};
    states state = BEG_MANT;
    while (true)
    {
        switch (state)
        {
        case BEG_MANT://beginning of mantisa
            if (isSign(str[0]))
            {
                state = ONE_DIG_MANT;
                str++;
            }
            else if (isDigit(str[0]))
            {
                state = DOT_OR_E;
                str++;
            }
            else
            {
                return false;
            }
            break;
        case ONE_DIG_MANT://one digit
            if (isDigit(str[0]))
            {
                state = DOT_OR_E;
                str++;
            }
            else
            {
                return false;
            }
            break;
        case DOT_OR_E://dot or exp
            if (isDot(str[0]))
            {
                state = ONE_DIG_AFTER_DOT;
                str++;
            }
            else if (isE(str[0]))
            {
                state = BEG_EXP;
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case ONE_DIG_AFTER_DOT://special for 'n.'
            if (isDigit(str[0]))
            {
                state = ANY_DIG_MANT;
                str++;
            }
            else
            {
                return false;
            }
            break;
        case ANY_DIG_MANT://any digits
            if (isDigit(str[0]))
            {
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else if (isE(str[0]))
            {
                state = BEG_EXP;
                str++;
            }
            else
            {
                return false;
            }
            break;
        case BEG_EXP://exponent
            if (isSign(str[0]))
            {
                state = ONE_DIG_EXP;
                str++;
            }
            else if (isDigit(str[0]))
            {
                state = ANY_DIG_EXP;
                str++;
            }
            else
            {
                return false;
            }
            break;
        case ONE_DIG_EXP://one digit
            if (isDigit(str[0]))
            {
                state = ANY_DIG_EXP;
                str++;
            }
            else
            {
                return false;
            }
            break;
        case ANY_DIG_EXP://any digits
            if (isDigit(str[0]))
            {
                str++;
            }
            else if (isEnd(str[0]))
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        default://strange situation
            break;
        }
    }
}
