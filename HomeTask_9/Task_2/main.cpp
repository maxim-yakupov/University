#include <iostream>

using namespace std;

const int codeShift = 31;
const int mult = 23;

int charStringLength(const char str[]);
long int pow(int base, int exp);
long int hashStr(char* str, unsigned int length);
bool compare(char* str1, char* str2);

int main()
{
    char* str1 = new char[500] {'\0'};
    char* str2 = new char[500] {'\0'};
    cout << "Write base string: ";
    cin.getline(str1, 500);
    cout << "Write string for search: ";
    cin.getline(str2, 500);
    unsigned int lengthStr1 = charStringLength(str1);
    unsigned int lengthStr2 = charStringLength(str2);
    long int hashForSearch = hashStr(str2, lengthStr2);
    long int hashCurrent = hashStr(str1, lengthStr2);

    long int multEdge = pow(mult, lengthStr2 - 1);
    unsigned int pos = lengthStr2 - 1;
    do
    {
        pos++;
        if (hashCurrent == hashForSearch)
        {
            cout << "hash match from position = " << pos - lengthStr2 << endl;
            cout << (compare(str2, &str1[pos - lengthStr2]) ? "FOUND!" : "false alarm(collision)") << endl;
        }
        hashCurrent = (-(str1[pos - lengthStr2] - codeShift) * multEdge + hashCurrent) * mult + str1[pos] - codeShift;
    } while (pos < lengthStr1);

    delete [] str1;
    delete [] str2;
    return 0;
}

int charStringLength(const char str[])
{
    int counter = 0;
    while (str[counter] != '\0')
    {
        counter++;
    }
    return counter;
}

bool compare(char* str1, char* str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return !*str1;
}

long int hashStr(char* str, unsigned int length)
{
    long int hash = str[0] - codeShift;
    unsigned int pos = 1;
    while (pos < length)
    {
        hash = (hash * mult + str[pos] - codeShift);
        pos++;
    }
    return hash;
}

long int pow(int base, int exp)
{
    long int answer = base;
    while (--exp)
    {
        answer *=base;
    }
    return answer;
}
