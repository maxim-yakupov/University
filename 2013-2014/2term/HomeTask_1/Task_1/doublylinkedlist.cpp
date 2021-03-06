#include "doublylinkedlist.h"

DoublyLinkedList::DoublyLinkedList()
{
}

DoublyLinkedList::~DoublyLinkedList()
{
    if (this->head)
    {
        while (this->head->next)
        {
            DLListElement* deleted = (DLListElement*)this->head->next;
            this->head->next = this->head->next->next;
            delete deleted;
        }
        delete this->head;
    }
}

void DoublyLinkedList::addValue(int value)
{
    DLListElement* current = (DLListElement*)this->head;
    if (this->length())
    {
        while(current->next)
        {
            current = (DLListElement*)current->next;
        }
        current->next = new DLListElement;
        current->next->elemValue = value;
        current->next->next = nullptr;
        ((DLListElement*)current->next)->prev = current;
    }
    else
    {
        this->head = new DLListElement;
        this->head->elemValue = value;
        this->head->next = nullptr;
        ((DLListElement*)this->head)->prev = nullptr;
    }
    this->size++;
}

void DoublyLinkedList::addPos(int pos, int value)
{
    DLListElement* current = (DLListElement*)this->head;
    if (pos >= this->length())
    {
        this->addValue(value);
    }
    else
    {
        while (current->next && (pos - 1))
        {
            current = (DLListElement*)current->next;
            pos--;
        }
        DLListElement* next = (DLListElement*)current->next;

        current->next = new DLListElement;
        current->next->elemValue = value;
        current->next->next = next;
        ((DLListElement*)current->next)->prev = current;

        this->size++;
    }
}

void DoublyLinkedList::deletePos(int pos)
{
    if (!this->length()) return;
    DLListElement* current = (DLListElement*)this->head;
    DLListElement* previous = (DLListElement*)this->head;
    if (!pos)
    {
        this->head = current->next;
        current->prev = nullptr;
        delete previous;
        this->size--;
        if (!this->size) this->head = nullptr;
        return;
    }
    while(current->next && (pos - 1))
    {
        previous = current;
        current = (DLListElement*)current->next;
        pos--;
    }
    if (current->next)
    {
        DLListElement* next = (DLListElement*)current->next->next;
        delete current->next;
        current->next = next;
        next->prev = current;
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
