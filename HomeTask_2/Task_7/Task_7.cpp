#include <iostream>
#include "stdlib.h"
#include "time.h"

using namespace std;

const int lengthOFNumber = 1;

void genSecretNum(char str[], int seed);
int bulls(char str[], char secret[]);
int cows(char str[], char secret[]);

int main()
{
    srand(time(NULL));
    int seed = rand() % 9999;
    char secretNum[lengthOFNumber + 1];
    genSecretNum(secretNum, seed);
    cout << "I has conceived the number. Try to guess it! (" << lengthOFNumber << " digits)" << endl;
    while (true)
    {
        char userNum[lengthOFNumber + 1];
        cout << ">> ";
        cin >> userNum;
        cout << endl;
        int amountBulls = bulls(userNum, secretNum);
        if (amountBulls != lengthOFNumber)
        {
            cout << "Cows: " << cows(userNum, secretNum) << " , Bulls: " << amountBulls << endl;
        }
        else
        {
            cout << "Correct!" << endl;
            break;
        };
    };
    return 0;
}

void genSecretNum(char str[], int seed)
{
    srand(seed);
    for (int i = 0; i < lengthOFNumber; i++)
    {
        str[i] = '0' + (rand() % 9);
        bool fl = true;
        while (fl)
        {
            fl = false;
            for(int j = 0; j < i; j++)
            {
                if (str[i] == str[j])
                {
                    str[i] = '0' + (rand() % 9);
                    fl = true;
                };
            };
        };
    };
}

int bulls(char str[], char secret[])
{
    int counter = 0;
    for (int i = 0; i < lengthOFNumber; i++)
    {
        if(str[i] == secret[i])
        {
            counter++;
        };
    };
    return counter;
}

int cows(char str[], char secret[])
{
    int counter = 0;
    for (int i = 0; i < lengthOFNumber; i++)
    {
        for (int j = 0; j < lengthOFNumber; j++)
        {
            if ((i != j) && (str[i] == secret[j]))
            {
                counter++;
                break;
            };
        };
    };
    return counter;
}
