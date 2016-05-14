#pragma once

namespace stringAPI
{
    struct String
    {
        char* beginning;
        int length;
    };
    String createString(void);
    void changeString(String& s, const char str[]);
    String createString(const char str[]);
    void concat(String &first, const String &second);
    bool areEqualStrings(const String &first, const String &second);
    int length(const String &s);
    bool isEmptyString(const String &s);
    String subString(const String &source, int pos, int quantity);
    String clone(const String& source);
    char* stringToCharPtr(const String &s);
    void deleteString(String& s);
}
