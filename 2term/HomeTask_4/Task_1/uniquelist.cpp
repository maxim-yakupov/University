#include "uniquelist.h"
#include <iostream>

UniqueList::UniqueList()
{
}

List::ListElement* UniqueList::contains(char* value)
{
    if (!size) return nullptr;
    unsigned int pos = 0;
    ListElement *element = head;
    do
    {
        char* eValue = element->elemValue;
        char* cValue = value;
        bool equal = (eValue[0] == cValue[0]);
        while (eValue[0] && equal)
        {
            eValue++;
            cValue++;
            equal = (eValue[0] == cValue[0]);
        }
        if (equal) return element;
        element = element->next;
        pos++;
    }
    while (element);
    return nullptr;
}

void UniqueList::addValue(char* value)
{
    ListElement* el = contains(value);
    if (!el)
    {
        SinglyLinkedList::addValue(value);
    }
    else
    {
        el->counter++;
    }
}

void UniqueList::deleteValue(char *value)
{
    if (!contains(value)) return;
    ListElement *element = head;
    int pos = 0;
    while (true)
    {
        char* eValue = element->elemValue;
        char* cValue = value;
        bool equal = (eValue[0] == cValue[0]);
        while (eValue[0] && equal)
        {
            eValue++;
            cValue++;
            equal = (eValue[0] == cValue[0]);
        }
        if (equal)
        {
            element->counter--;
            if (!element->counter)
            {
                deletePos(pos);
            }
            break;
        }
        pos++;
        element = element->next;
    }
}

void UniqueList::print()
{
    ListElement* current = this->head;
    if (current)
    {
        std::cout << current->elemValue << "{" << current->counter << "}";
        while (current->next)
        {
            current = current->next;
            std::cout << "->" << current->elemValue << "{" << current->counter << "}";
        }
    }
    else
    {
        std::cout << "(empty)";
    }
    std::cout << "\n";
}

List::ListElement *UniqueList::retH()
{
    return head;
}
