#include <iostream>

using namespace std;

struct Pare
{
    int value;
    unsigned int counter;
};

void add(int input, Pare*& pares, unsigned int& size);
void sortArray(Pare* pares, unsigned int leftLimiter, unsigned int rightLimiter);
void writeArray(Pare* pares, unsigned int size);

int main()
{
    Pare* pares = new Pare[1];

    unsigned int size = 0;
    int input = 0;
    cout << "Write sequence of numbers('-1' is end of input):" << endl;
    cin >> input;
    while (input != -1)
    {
        add(input, pares, size);
        cin >> input;
    }

    sortArray(pares, 0, size - 1);
    writeArray(pares, size);

    delete [] pares;
    return 0;
}

void add(int input, Pare*& pares, unsigned int& size)
{
    bool wasFound = false;
    unsigned int i = 0;
    while (!wasFound)
    {
        if (i == size)
        {
            break;
        }
        else if (pares[i].value == input)
        {
            pares[i].counter++;
            wasFound = true;
            break;
        }
        i++;
    }
    if (!wasFound)
    {
        Pare* updated = new Pare[size + 1];
        for (unsigned int i = 0; i < size; i++)
        {
            updated[i] = pares[i];
        }
        updated[size].value = input;
        updated[size].counter = 1;
        delete [] pares;
        pares = updated;
        size++;
    }
}

void swapPares(unsigned int first, unsigned int second, Pare* pares)
{
    int tValue = pares[first].value;
    int tCounter = pares[first].counter;
    pares[first].value = pares[second].value;
    pares[first].counter = pares[second].counter;
    pares[second].value = tValue;
    pares[second].counter = tCounter;
}

void sortArray(Pare* pares,unsigned int leftLimiter, unsigned int rightLimiter)
{
    if (leftLimiter == rightLimiter - 1)
    {
        if (pares[leftLimiter].value < pares[rightLimiter].value)
        {
            swapPares(leftLimiter, rightLimiter, pares);
        };
    }
    else if (leftLimiter != rightLimiter)
    {
        const int base = pares[rightLimiter].value;
        int left = leftLimiter;
        int right = rightLimiter;
        while (left <= right)
        {
            while ((left <= rightLimiter) && (pares[left].value >= base))
            {
                left++;
            };
            while ((right >= leftLimiter) && (pares[right].value < base))
            {
                right--;
            };
            if (left < right)
            {
                swapPares(left, right, pares);
            }
            else
            {
                if (left <= rightLimiter)
                {
                    sortArray(pares, left, rightLimiter);
                    sortArray(pares, leftLimiter, left - 1);
                }
                else
                {
                    sortArray(pares, leftLimiter, right - 1);
                    sortArray(pares, right, rightLimiter);
                };
            };
        };
    };
}

void writeArray(Pare* pares, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        cout << "number: " << pares[i].value << " quantity: " << pares[i].counter << endl;
    }
}
