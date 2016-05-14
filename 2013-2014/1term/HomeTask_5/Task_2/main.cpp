#include <iostream>
#include <bitset>//для прямого вывода двоичного представления

using namespace std;

int calcExponent(unsigned char* t)
{
    unsigned char bit = 0b00000001;
    long int exponenta = 0;
    int mult = 1;
    bit = 0b00010000;
    t--;
    while (bit != 0b00000000)
    {
        if (bit & *t)
        {
            exponenta += mult;
        }
        mult *= 2;
        bit <<= 1;
    }
    t++;
    bit = 0b00000001;
    while (bit != 0b10000000)
    {
        if (bit & *t)
        {
            exponenta += mult;
        }
        mult *= 2;
        bit <<= 1;
    }

    return exponenta - 1023;
}

long double calcMantise(unsigned char* t)
{
    long double mantisa = 1.0;
    unsigned char bit = 0b00001000;
    long double mult = 0.5;
    while (bit != 0b00000000)
    {
        if (bit & *t)
        {
            mantisa += mult;
        }
        mult /= 2;
        bit >>= 1;
    }
    for (int i = 0; i < 6; i++)
    {
        t--;
        bit = 0b10000000;
        while (bit != 0b00000000)
        {
            if (bit & *t)
            {
                mantisa += mult;
            }
            mult /= 2;
            bit >>= 1;
        }
    }
    return mantisa;
}

int main()
{
    double number;
    cout << "Write number: ";
    cin >> number;
    cout << "Binary representation in memory: " << endl;
    unsigned char* t = (unsigned char*)(&number + 1);
    for (int j = 0; j < 8; j++)
    {
        t--;
        cout << bitset<8>(*t) << " ";
    }
    cout << endl;
    cout << "Result: ";
    //int bit = 0b10000000;
    t = (unsigned char*)(&number + 1);
    t--;
    if (/*bit*/0b10000000 & *t)
    {
        cout << "-";
    }
    else
    {
        cout << "+";
    }
    int ex = calcExponent(t);
    t--;
    long double mant = calcMantise(t);
    cout << mant << "*2^(" << ex << ")";
    return 0;
}

