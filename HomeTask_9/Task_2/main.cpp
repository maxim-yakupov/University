#include <iostream>

using namespace std;

int charStringLength(const char str[]);

int main()
{
    char* str1 = new char[500] {'\0'};
    char* str2 = new char[500] {'\0'};
    cout << "Write base string: ";
    cin.getline(str1, 500);
    cout << "Write string for search: ";
    cin.getline(str2, 500);
    int lengthStr1 = charStringLength(str1);
    int lengthStr2 = charStringLength(str2);
    long int hashForSearch = hashStr(str2, lengthStr2);


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
long int hashChar(char ch)
{

}

long int hashStr(char* str, int length)
{

}
