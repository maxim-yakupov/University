#include "singlylinkedlist.h"

SinglyLinkedList::SinglyLinkedList()
{
}

SinglyLinkedList::~SinglyLinkedList()
{
    if (this->head)
    {
        while (this->head->next)
        {
            SLListElement* deleted = (SLListElement*)this->head->next;
            this->head->next = this->head->next->next;
            delete deleted;
        }
        delete this->head;
    }
}

unsigned int strln(const char* str)//0-byte also counts
{
    unsigned int counter = 0;
    for (int i = 0; str[i]; i++)
    {
        counter++;
    }
    return counter + 1;
}

char* copyStr(const char* str)
{
    unsigned int length = strln(str);
    char* newStr = new char[length];
    for (unsigned int i = 0; i < length; i++)
    {
        newStr[i] = str[i];
    }
    return newStr;
}

void SinglyLinkedList::addValue(const char* value)
{
    char* valueCopy = copyStr(value);
    SLListElement* current = (SLListElement*)this->head;
    if (this->length())
    {
        while(current->next)
        {
            current = (SLListElement*)current->next;
        }
        current->next = new SLListElement;
        current->next->elemValue = valueCopy;
        current->next->counter = 1;
        current->next->next = nullptr;
    }
    else
    {
        this->head = new SLListElement;
        this->head->elemValue = valueCopy;
        this->head->counter = 1;
        this->head->next = nullptr;
    }
    this->size++;
}

void SinglyLinkedList::addPos(int pos, char* value)
{
    SLListElement* current = (SLListElement*)this->head;
    if (pos >= this->length())
    {
        this->addValue(value);
    }
    else
    {
        while (current->next && (pos - 1))
        {
            current = (SLListElement*)current->next;
            pos--;
        }
        SLListElement* next = (SLListElement*)current->next;

        value = copyStr(value);
        current->next = new SLListElement;
        current->next->elemValue = value;
        current->next->counter = 1;
        current->next->next = nullptr;

        current->next->next = next;
        this->size++;
    }
}

void SinglyLinkedList::deletePos(int pos)
{
    if (!this->length()) return;
    SLListElement* current = (SLListElement*)this->head;
    SLListElement* previous = (SLListElement*)this->head;
    if (!pos)
    {
        this->head = current->next;
        delete previous;
        this->size--;
        if (!this->size) this->head = nullptr;
        return;
    }
    while(current->next && (pos - 1))
    {
        previous = current;
        current = (SLListElement*)current->next;
        pos--;
    }
    if (current->next)
    {
        SLListElement* next = (SLListElement*)current->next->next;
        delete current->next;
        current->next = next;
    }
    else
    {
        previous->next = nullptr;
        delete current;
    }
    this->size--;
    if (!this->size)
    {
        this->head = nullptr;
    }
}
