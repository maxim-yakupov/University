#include <iostream>
#include "doublylinkedlist.h"

DoublyLinkedList::DoublyLinkedList(int value):List(value)
{
    prev = nullptr;
//    std::cout << "\nDebug:constrDLList " << this->elemValue << "\n";
}

DoublyLinkedList::~DoublyLinkedList()
{
//    std::cout << "\nDebug:destrDLList " << this->elemValue << "\n";
}

void DoublyLinkedList::addValue(int value)
{
    DoublyLinkedList* current = this;
    while(current->next)
    {
        current = (DoublyLinkedList*)current->next;
    }
    current->next = new DoublyLinkedList(value);
    ((DoublyLinkedList*)current->next)->prev = current;
}

void DoublyLinkedList::addPos(int pos, int value)
{
    DoublyLinkedList* current = this;
    if (pos >= this->length())
    {
        this->addValue(value);
    }
    else
    {
        while (current->next && (pos - 1))
        {
            current = (DoublyLinkedList*)current->next;
            pos--;
        }
        DoublyLinkedList* next = (DoublyLinkedList*)current->next;
        current->next = new DoublyLinkedList(value);
        ((DoublyLinkedList*)current->next)->next = next;
    }
}

void DoublyLinkedList::deletePos(int pos)
{
    DoublyLinkedList* current = this;
    DoublyLinkedList* previous = this;
    while(current->next && (pos - 1))
    {
        previous = current;
        current = (DoublyLinkedList*)current->next;
        pos--;
    }
    if (current->next)
    {
        DoublyLinkedList* next = (DoublyLinkedList*)((DoublyLinkedList*)current->next)->next;
        delete (DoublyLinkedList*)current->next;
        current->next = next;
    }
    else
    {
        previous->next = nullptr;
        delete (DoublyLinkedList*)current;
    }
}

void DoublyLinkedList::deleteList()
{
    while (next)
    {
        DoublyLinkedList* deleted = (DoublyLinkedList*)next;
        next = (DoublyLinkedList*)((DoublyLinkedList*)next)->next;
        delete (DoublyLinkedList*)deleted;
    }
}
