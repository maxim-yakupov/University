#include "uniquelist.h"

UniqueList::UniqueList()
{
}

bool UniqueList::contains(int value)
{
    if (!size) return false;
    ListElement *element = head;
    do
    {
        if (element->elemValue == value) return true;
        element = element->next;
    }
    while (element);
    return false;
}

void UniqueList::addValue(int value)
{
    if (contains(value)) throw Exceptions::AddsExistingValue();
    SinglyLinkedList::addValue(value);
}

void UniqueList::addPos(int pos, int value)
{
    if (contains(value)) throw Exceptions::AddsExistingValue();
    SinglyLinkedList::addPos(pos, value);
}

void UniqueList::deleteValue(int value)
{
    if (!contains(value)) throw Exceptions::DeletesNotExistingValue();
    ListElement *element = head;
    int pos = 0;
    while (true)
    {
        if (element->elemValue == value)
        {
            deletePos(pos);
            break;
        }
        pos++;
        element = element->next;
    }
}
