#include <iostream>

using namespace std;

unsigned int fibonachi(unsigned int step);

int main()
{
    cout << "Write number of Fibonachi number: ";
    unsigned int n = 0;
    cin >> n;
    cout << "Fib(" << n << ") = " << fibonachi(n);
    return 0;
}

unsigned int fibonachi(unsigned int step)
{
    if (!step)
    {
        return 0;
    }
    else if (step == 1)
    {
        return 1;
    }
    else
    {
        return fibonachi(step - 1) + fibonachi(step - 2);
    }
}
