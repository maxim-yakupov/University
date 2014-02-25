#include <iostream>

using namespace std;

int main()
{
    int n = 1;
    const int maxSizeOfArray = 5000;
    bool array[maxSizeOfArray] = {true};
    cout << "Enter the limiter [1 < n < " << maxSizeOfArray << "] : ";
    cin >> n;
    cout << endl;
    for (int i = 1; i <= n; i++)
    {
        array[i] = true;
    };
    cout << "List of 'simple numbers':" << endl;
    cout << 1 << endl;
    for (int i = 2; i <= n; i++)
    {
        if (array[i])
        {
            cout << i << endl;
            for (int j = i + i; j <= n; j += i)
            {
                array[j] = false;
            };
        };
    };
    return 0;
}
