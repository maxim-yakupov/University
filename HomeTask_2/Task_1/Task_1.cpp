#include <iostream>

using namespace std;

unsigned long int recFib(int baseFib);

unsigned long int itFib(int baseFib);

int main()
{
    int baseFib = 1;
    cout << "Enter the base of fibonacci consequence: ";
    cin >> baseFib;
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
            cout << baseFib << " fibonacci number = " << recFib(baseFib);
            break;
        };
        //
        case 'i':
        {
            cout << baseFib << " fibonacci number = " << itFib(baseFib);
            break;
        };
        //
        default:
        {
            cout << baseFib << " fibonacci number = " << itFib(baseFib);
            break;
        };
    };
    cout << endl;
    return 0;
}

unsigned long int recFib(int baseFib)
{
    if ((baseFib == 1) || (baseFib == 2))
    {
        return 1;
    }
    else
    {
        return recFib(baseFib - 1) + recFib(baseFib - 2);
    };
}

unsigned long int itFib(int baseFib)
{
    unsigned long int fib_first = 1;
    unsigned long int fib_second = 1;
    unsigned long int fib_current = 1;
    for (int i = 3; i <= baseFib; i++)
    {
        fib_current = fib_first + fib_second;
        fib_first = fib_second;
        fib_second = fib_current;
    };
    return fib_current;
}
