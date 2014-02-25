#include <iostream>

using namespace std;

int main()
{
    cout << "F(x) = x^4 + x^3 + x^2 + x. Enter value of x:";
    double x = 0;
    cin >> x;
    double sqrX = x * x;
    cout << endl << "F(" << x << ") = " << (sqrX + 1) * (sqrX + x) << endl;
    return 0;
}

