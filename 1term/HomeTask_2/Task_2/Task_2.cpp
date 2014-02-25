#include <iostream>

using namespace std;

unsigned long pow(int x, int partOfDegree);

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
    cout << "a^n = ";
    if (n < 0)
    {
        cout << "1 / ";
    };
    cout << pow(a, n) << endl;
    return 0;
}

//моя интерпретация этого алгоритма http://ru.wikipedia.org/wiki/Алгоритм_быстрого_возведения_в_степень
unsigned long int pow(int x, int partOfDegree)
{
    if (partOfDegree != 0)
    {
        int xCurrent = x;
        int currentBinDegree = partOfDegree % 2;
        if (currentBinDegree == 0)
        {
            xCurrent = 1;
        };
        unsigned long int nextStep = pow(x, partOfDegree / 2);
        nextStep *= nextStep;
        return xCurrent * nextStep;
    }
    else
    {
        return 1;
    };
}

