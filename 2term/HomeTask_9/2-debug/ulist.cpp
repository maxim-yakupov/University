#include "ulist.h"

UList::UList()
{
}

UList::~UList()
{
}

int UList::length()
{
    return PList::length();
}

void UList::add(int value, int num)
{
    if (!exist(value))
    {
        PList::add(value, num);
    }
    else
    {
        throw AddingExistingItem();
    }
}

void UList::del(int num)
{
    PList::del(num);
}

void UList::removeList()
{
    PList::removeList();
}

int UList::returnValue(int num)
{
    return PList::returnValue(num);
}

void UList::printList()
{
    PList::printList();
}

void UList::swap(int i, int j)
{
    PList::swap(i, j);
}

bool UList::exist(int value)
{
    Node *prevNode = head;
    while(prevNode->next)
    {
        prevNode = prevNode->next;
        if (prevNode->value == value)
            return true;
    }
    return false;
}

void UList::delValue(int value)
{
    if (exist(value))
    {
        Node *prevNode = head;
        while (prevNode->next->value != value)
        {
            prevNode = prevNode->next;
        }
        Node *deletingNode = prevNode->next;
        prevNode->next = deletingNode->next;
        delete deletingNode;
    }
    else
    {
        throw RemovingNotExistingItem();
    }
}
