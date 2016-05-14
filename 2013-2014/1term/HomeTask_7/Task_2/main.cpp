#include <iostream>
#include "maxstring.h"

using namespace std;
using namespace stringAPI;

const int maxStringLength = 500;

void refreshCString(char*& s)
{
    delete[] s;
    s = new char[maxStringLength];
}

int main()
{
    char* inChar;
    refreshCString(inChar);

    String s = createString("Hello S");
    cout << "Our string s is:'"
         << stringToCharPtr(s)
         << "' with length "
         << length(s)
         << " and emptyness is "
         << isEmptyString(s)
         << endl;

    String s2 = createString("uBye");
    cout << "Our string s2 is:'"
         << stringToCharPtr(s2)
         << "' with length "
         << length(s2)
         << " and emptyness is "
         << isEmptyString(s2)
         << endl;

    concat(s, s2);
    cout << "Our string s is:'"
         << stringToCharPtr(s)
         << "' with length "
         << length(s)
         << " and emptyness is "
         << isEmptyString(s)
         << endl;

    String s3 = createString();
    cout << "Write value of string s3: ";
    cin.getline(inChar, 500);

    changeString(s3, inChar);
    refreshCString(inChar);
    cout << "Our string s3 is:'"
         << stringToCharPtr(s3)
         << "' with length "
         << length(s3)
         << " and emptyness is "
         << isEmptyString(s3)
         << endl;
    cout << "equality of s & s3 = "
         << areEqualStrings(s, s3)
         << endl;

    String s4 = createString();
    s4 = subString(s, 6, 3);
    cout << "substring of s from 6th (3 symbols): "
         << stringToCharPtr(s4)
         << endl;

    changeString(s4, "i'm changed");
    cout << "changed s4: "
         << stringToCharPtr(s4)
         << endl;

    deleteString(s); cout << "\n!del s\n";
    deleteString(s2); cout << "!del s2\n";
    deleteString(s3); cout << "!del s3\n";
    deleteString(s4); cout << "!del s4\n";

    s = createString("123");
    cout << "s: "
         << stringToCharPtr(s)
         << endl;
    s4 = clone(s);
    cout << "s4('"
         << stringToCharPtr(s4)
         << "') cloned from s"
         << endl;

    deleteString(s); cout << "\n!del s\n";
    deleteString(s4); cout << "!del s4\n";

    delete[] inChar;
    return 0;
}

