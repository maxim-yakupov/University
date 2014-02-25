#include <iostream>

using namespace std;

unsigned long int recFactorial(int n);

unsigned long int itFactorial(int n);

int main()
{
    int n = 1;
    cout << "Enter the base of factorial (n!) : n = ";
    cin >> n;
    cout << endl;
    cout << "[R]ecursive or [i]terative algorithm?";
    cout << endl;
    cout << ">>";
    char choice = 'R';
    cin >> choice;
    cout << endl;
    switch (choice)
    {
        case 'R':
        {
            cout << "n! = " << recFactorial(n);
            break;
        };
        //
        case 'i':
        {
            cout << "n! = " << itFactorial(n);
            break;
        };
        //
        default:
        {
            cout << "n! = " << itFactorial(n);
            break;
        };
    };
    cout << endl;
    return 0;
}

unsigned long int recFactorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * recFactorial(n - 1);
    };
}

unsigned long int itFactorial(int n)
{
    unsigned long int factorial = 1;
    for (int i = 1; i <= n; i++)
    {
        factorial *= i;
    };
    return factorial;
}
