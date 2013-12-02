#pragma once

namespace stringAPI
{
    struct String
    {
        char* beginning;
        int length;
    };
    String createString();
    void changeString(String& s, char str[]);
    void concat(String &first, String second);
    void clone(String& destination, String source);
    bool areEqualStrings(String first, String second);
    int length(String s);
    bool isEmptyString(String s);
    String subString(String source, int pos, int quantity);
    char* stringToCharPtr(String &s);
    void MYdeleteString(String& s);
}
