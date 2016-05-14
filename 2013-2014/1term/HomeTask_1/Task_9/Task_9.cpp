#include <iostream>
#include <stdlib.h>//abs()

using namespace std;

int main()
{
    cout << "This progam will compute the expression: a^n" << endl;
    cout << "Enter a: ";
    long double a = 0;
    cin >> a;
    cout << endl;
    cout << "Enter n: ";
    int n = 1;
    cin >> n;
    cout << endl;
    long double result = a;
    if (n != 0)
    {
        for (int i = 2; i <= abs(n); i++)
        {
            result *= a;
        };
    }
    else
    {
        a = 1;
    };
    cout << "a^n = ";
    if (n < 0)
    {
        cout << "1 / ";
    };
    cout << result << endl;
    return 0;
}

