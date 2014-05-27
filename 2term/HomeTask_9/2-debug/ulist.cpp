#include "ulist.h"

UList::UList()
{
    head = new Node;
    head->value = 0;
    head->next = NULL;
}

UList::~UList()
{
    removeList();
    delete head;
}

int UList::length()
{
    return PList::length();
}

void UList::add(int value, int num)
{
    if (!exist(value))
        PList::add(value, num);
    else
    {
        try
        {
            throw AddingExistingItem();
        }
        catch(AddingExistingItem) {}
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
    Node *tmp = head;
    while(tmp->next)
    {
        tmp = tmp->next;
        if (tmp->value == value)
            return true;
    }
    return false;
}

void UList::delValue(int value)
{
    if (exist(value))
    {
        Node *tmp = head;
        while (tmp->next->value != value)
        {
            tmp = tmp->next;
        }
        Node *tmp2 = tmp->next;
        tmp->next = tmp2->next;
        delete tmp2;
    }
    else
    {
        try
        {
            throw RemovingExistingItem();
        }
        catch(RemovingExistingItem) {}
    }

}
