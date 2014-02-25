#include <iostream>

using namespace std;

//Перефразируем условие - нужно вывести ряд Фарея n-го порядка,
//не включая 0 и 1 http://ru.wikipedia.org/wiki/Ряд_Фарея

void insertElem(int fArray[], int sArray[], int pointer, int limiter);
void swap(int array[],int first, int second);

int main()
{
    const int arrayLength = 50;
    int numerators[arrayLength];
    numerators[0] = 0;
    numerators[1] = 1;

    int denominators[arrayLength];
    denominators[0] = 1;
    denominators[1] = 1;

    int numberOfElems = 2;

    cout << "Enter maximal denominator: ";
    int maxDenominator = 1;
    cin >> maxDenominator;

    for (int i = 1; i < maxDenominator; i++)
    {
        int currentPos = 1;
        while (currentPos < numberOfElems)
        {
            if (denominators[currentPos - 1] + denominators[currentPos] <= i + 1)
            {
                insertElem(numerators, denominators, currentPos, numberOfElems);
                numberOfElems++;
            };
            currentPos++;
        };
    };

    for (int i = 1; i < numberOfElems - 1; i++)
    {
        cout << "(" << numerators[i] << "/" << denominators[i] << ") " /*<< endl*/; //раскомментировать для построчного вывода
    };

    return 0;
}

void insertElem(int fArray[], int sArray[], int pointer, int limiter)
{
    while (limiter > pointer)
    {
        swap(fArray, limiter, limiter - 1);
        swap(sArray, limiter, limiter - 1);
        limiter--;
    };
    fArray[pointer] = fArray[pointer - 1] + fArray[pointer + 1];
    sArray[pointer] = sArray[pointer - 1] + sArray[pointer + 1];
}

void swap(int array[],int first, int second)
{
    int temp = array[first];
    array[first] = array[second];
    array[second] = temp;
}
