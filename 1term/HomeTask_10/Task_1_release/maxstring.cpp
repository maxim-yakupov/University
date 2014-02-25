#include "maxstring.h"

int charStringLength(const char str[])
{
    int counter = 0;
    while (str[counter] != '\0')
    {
        counter++;
    }
    return counter;
}

namespace stringAPI
{
    String createString(void)
    {
        return String {nullptr, 0};
    }

    void changeString(String& s, const char str [])
    {
        int lengthCh = charStringLength(str);
        delete[] s.beginning;
        s.beginning = new char[lengthCh + 1];
        s.length = 0;
        while (length(s) != lengthCh)
        {
            s.beginning[length(s)] = str[length(s)];
            s.length++;
        }
        s.beginning[length(s)] = '\0';
    }

    String createString(const char str [])
    {
        String result = createString();
        changeString(result, str);
        return result;
    }

    void concat(String& first, const String& second)
    {
        char* result = new char[length(first) + length(second) + 1];
        for (int i = 0; i < length(first); i++)
        {
            result[i] = first.beginning[i];
        }
        int startLength = length(first);
        int i = 0;
        while (length(first) != (startLength + length(second)))
        {
            result[length(first)] = second.beginning[i];
            i++;
            first.length++;
        }
        result[length(first)] = '\0';
        delete[] first.beginning;
        first.beginning = result;
    }

    bool areEqualStrings(const String& first, const String& second)
    {
        if (first.length != second.length)
        {
            return false;
        }
        else
        {
            int pos = 0;
            while (pos < first.length)
            {
                if (first.beginning[pos] != second.beginning[pos])
                {
                    return false;
                }
                pos++;
            }
            return true;
        }
    }

    int length(const String& s)
    {
        return s.length;
    }

    bool isEmptyString(const String& s)
    {
        return (s.length == 0);
    }

    String subString(const String& source, int pos, int quantity)
    {
        String subStr = createString();
        subStr.beginning = new char[quantity + 1];
        while (subStr.length != quantity)
        {
            int subStrLength = length(subStr);
            subStr.beginning[subStrLength] = source.beginning[pos + subStrLength];
            subStr.length++;
        }
        subStr.beginning[quantity] = '\0';
        return subStr;
    }

    String clone(const String& source)
    {
        return subString(source, 0, source.length);
    }

    char* stringToCharPtr(const String& s)
    {
        return s.beginning;
    }

    void deleteString(String& s)
    {
        delete[] s.beginning;
        s.beginning = nullptr;
        s.length = 0;
    }
}
