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

void SinglyLinkedList::addValue(int value)
{
    SLListElement* current = (SLListElement*)this->head;
    if (this->length())
    {
        while(current->next)
        {
            current = (SLListElement*)current->next;
        }
        current->next = new SLListElement;
        current->next->elemValue = value;
        current->next->next = nullptr;
    }
    else
    {
        this->head = new SLListElement;
        this->head->elemValue = value;
        this->head->next = nullptr;
    }
    this->size++;
}

void SinglyLinkedList::addPos(int pos, int value)
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

        current->next = new SLListElement;
        current->next->elemValue = value;
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
