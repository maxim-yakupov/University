#pragma once

/*
 * List abstract class
 */

class List
{
public:
    List();
    virtual ~List();
    unsigned int length();//returns length of list
    virtual void addValue(const char* value) = 0;//adds last element
    virtual void addPos(int pos, char* value) = 0;//adds on position or last element
    virtual void deletePos(int pos) = 0;//deletes element from position or last element
    virtual void print();//prints list
protected:
    struct ListElement
    {
        char* elemValue;
        unsigned int counter;
        ListElement* next;
        ~ListElement()
        {
            delete elemValue;
        }
    };
    ListElement* head;
    unsigned int size;
};
