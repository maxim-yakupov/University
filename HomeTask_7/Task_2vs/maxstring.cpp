#include "maxstring.h"

int charStringLength(char/***/ str[])
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
    String createString()
    {
		String t;
		t.beginning = nullptr;
		t.length = 0;
        return t;
    }

    void changeString(String& s, char str [])
    {
        int lengthCh = charStringLength(str);
        if (s.beginning) delete[] s.beginning;
        s.beginning = new char[lengthCh];
        s.length = 0;
        while (length(s) != lengthCh)
        {
            s.beginning[length(s)] = str[length(s)];
            s.length++;
        }
        s.beginning[length(s)] = '\0';
    }

    void concat(String& first, String second)
    {
        char* result = new char[length(first) + length(second)];
        for (int i = 0; i < length(first); i++)
        {
            result[i] = first.beginning[i];
        }
        int startLength = length(first);
        while (length(first) != (startLength + length(second)))
        {
            result[length(first)] = second.beginning[0];
            second.beginning = &second.beginning[1];
            first.length++;
        }
        result[length(first)] = '\0';
        //if (first.beginning) delete[] first.beginning;
        first.beginning = result;
    }

    void clone(String& destination, String source)
    {
        if (destination.beginning) delete[] destination.beginning;
        destination.beginning = new char[length(source)];
        destination.length = source.length;
        int pos = 0;
        while (pos < destination.length)
        {
            destination.beginning[pos] = source.beginning[pos];
            pos++;
        }
    }

    bool areEqualStrings(String first, String second)
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

    int length(String s)
    {
        return s.length;
    }

    bool isEmptyString(String s)
    {
        return s.length ? false : true;
    }

    String subString(String source, int pos, int quantity)
    {
        String subStr = createString();
        subStr.beginning = new char[quantity];
        while (subStr.length != quantity)
        {
            int subStrLength = length(subStr);
            subStr.beginning[subStrLength] = source.beginning[pos + subStrLength];
            subStr.length++;
        }
        subStr.beginning[quantity] = '\0';
        return subStr;
    }

    char* stringToCharPtr(String& s)
    {
        return s.beginning;
    }

    void MYdeleteString(String& s)
    {
        if (s.beginning) delete[] s.beginning;
        s.beginning = nullptr;
        s.length = 0;
    }
}
