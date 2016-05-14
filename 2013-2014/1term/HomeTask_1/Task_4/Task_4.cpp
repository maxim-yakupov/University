#include <iostream>

using namespace std;

int main()
{
    const int maxNum = 9;
    const int maxSummOfThreeNums = 27;
    int summ[maxSummOfThreeNums] = {0};
    for (int i = 0; i <= maxNum; i++)
    {
        for (int j = 0; j <= maxNum; j++)
        {
            for (int k = 0; k <= maxNum; k++)
            {
                summ[i + j + k]++;
            };
        };
    };
    unsigned int summary = 0;
    for (int i = 0; i <= maxSummOfThreeNums; i++)
    {
        summary += summ[i] * summ[i];
    };
    cout << "Amount of 'lucky' tikkets = " << summary << endl;
    return 0;
}

