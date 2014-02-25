#include <iostream>
#include "polynome.h"

using namespace std;
using namespace Polynomes;

void readPolynome(Polynome* polynome); //depends on task, so not in module
void writePolynome(Polynome* polynome); //depends on task, so not in module

int main()
{
    Polynome* polyOne = createPolynome();
    readPolynome(polyOne);
    cout << "\nF(x)=";    writePolynome(polyOne);


    Polynome* polyTwo = createPolynome();
    readPolynome(polyTwo);
    cout << "\nG(x)=";    writePolynome(polyTwo);


    int x = 0;
    cout << "\n\nWrite x: ";
    cin >> x;

    cout << "\nF(" << x << ")=" << value(polyOne, x);
    cout << "\nG(" << x << ")=" << value(polyTwo, x);

    Polynome* polySum = createPolynome();
    add(polyOne, polyTwo, polySum);
    cout << "\n\n(F+G)(x)=";    writePolynome(polySum);

    cout << "\n\nF(" << x << ")+G(" << x << ")=" << value(polyOne, x) + value(polyTwo, x);
    cout << "\n(F+G)(" << x << ")=" << value(polySum, x);

    cout << "\n\nF() and G() are " << (equals(polyOne, polyTwo) ? "equal" : "NOT equal");

    deletePolynome(polyOne);
    deletePolynome(polyTwo);
    deletePolynome(polySum);

    return 0;
}

void writePolynome(Polynome* polynome)
{
    Member* current = polynome->highExp;
    while (current)
    {
        cout << ((current != polynome->highExp && current->multiplier >= 0) ? "+" : "") << current->multiplier << "x^" << current->exp;
        current = current->next;
    }
}

bool isDigit(char current)
{
    return (current >= '0') && (current <= '9');
}

void readPolynome(Polynome* polynome)
{
    cout << "\nWrite polynome's coefficients & exponents[of type int](don't check if correct!)"
         << "\nExample:---------"
         << "\nYour polynome: 4x^4+3x^2-2x^1-56x^0"
         << "\nYour type: 4 4 3 2 -2 1 -56 0"
         << "\n-----------------\n";
    char current = getchar();
    bool fl = true;
    int coef = 0;
    int exp = 0;
    bool minus = false;
    while ((current < 20) || (current == ' ') || (current == '-') || ((current >= '0') && (current <= '9')))
    {
        if (isDigit(current))
        {
            if (fl)
            {
                coef = coef * 10 + current - '0';
            }
            else
            {
                exp = exp * 10 + current - '0';
            }
        }
        else
        {
            if (current == '-')
            {
                minus = true;
            }
            else
            {
                if (fl)
                {
                    fl = false;
                    if (minus)
                    {
                        coef *= -1;
                    }
                    minus = false;
                }
                else
                {
                    fl = true;
                    if (minus)
                    {
                        exp *= -1;
                    }
                    minus = false;
                    addMember(polynome, coef, exp);
                    coef = 0;
                    exp = 0;
                    if (current != ' ')
                    {
                        break;
                    }
                }
            }
        }
        current = getchar();
    }
}
