#include <iostream>
#include <cstring> //для работы strlen()

using namespace std;

void dissociation(char str[], int sum, int summand);

int main()
{
    const int strLength = 100;
    cout << "Enter your number >= 2: ";
    int num = 2;
    cin >> num;
    cout << endl;
    cout << "Representations of your number as a sum of terms:" << endl << endl;
    for (int i = num - 1; i >= 1; i--)
    {
        char str[strLength] = {'\0'};
        str[0] = '0' + i;
        dissociation(str, num, i);
    };
    return 0;
}

void dissociation(char str[], int sum, int summand)
{
    if ((sum - summand) == 0)
    {
        cout << str << endl;
    }
    else
    {
        int strPos = strlen(str);
        for (int i = sum - summand; i >= 1; i--)
        {
            if (i <= summand)
            {
                str[strPos] = '+';
                str[strPos + 1] = '0' + i;
                dissociation(str, sum - summand, i);
            };
        };
    };
}
