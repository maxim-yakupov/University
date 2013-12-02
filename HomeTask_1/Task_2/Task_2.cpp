#include <iostream>

using namespace std;

int main()
{
    cout << "Enter 'a' and 'b' (with space between numbers): ";
    int a = 0;
    int b = 0;
    int counter = 0;
    cin >> a >> b;
    cout << endl;
    while (a >= b)
    {
        counter++;
        a -= b;
    };
    cout << "a / b = " << counter;
    return 0;
}

