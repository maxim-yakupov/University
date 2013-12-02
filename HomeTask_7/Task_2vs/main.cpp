#include <iostream>
#include "maxstring.h"

using namespace std;
using namespace stringAPI;

int main()
{
    String s = createString();
    changeString(s, "Hello");
    cout << "Our string s is:'" << stringToCharPtr(s) << "' with length " << length(s)<< " and emptyness is " << isEmptyString(s) << endl;

    String s2 = createString();
    changeString(s2, "Bye");
    cout << "Our string s2 is:'" << stringToCharPtr(s2) << "' with length " << length(s2)<< " and emptyness is " << isEmptyString(s2) << endl;

    concat(s, s2);
    cout << "Our string s is:'" << stringToCharPtr(s) << "' with length " << length(s)<< " and emptyness is " << isEmptyString(s) << endl;

    String s3 = createString();
    char/***/ input[20]/* = new char[999]*/;
    cin >> input;
    changeString(s3, input);
    cout << "Our string s3 is:'" << stringToCharPtr(s3) << "' with length " << length(s3)<< " and emptyness is " << isEmptyString(s3) << endl;
    cout << "equality of s & s3 = " << areEqualStrings(s, s3) << endl;

    String s4 = createString();
    cout << "!1";
    changeString(s4, "dsf");
    //s4 = subString(s, 3, 3); cout << "!";
    //cout << stringToCharPtr(s4) << endl; cout << "!";

    //changeString(s4, "changed"); cout << "!";
    cout << stringToCharPtr(s4) << endl;
    cout << "!2";
/*
    MYdeleteString(s); cout << "!";
    //MYdeleteString(s4);
    //MYdeleteString(s2);

    MYdeleteString(s3); cout << "!";
*/
    cout << stringToCharPtr(s) << endl; cout << "!3";
	cin >> input;
    return 0;
}

