#include "list.h"
#include <iostream>

List::List(int value)
{
    elemValue = value;
    next = nullptr;
//    std::cout << "\nDebug:constrList " << this->elemValue << "\n";
}

List::~List()
{
//    std::cout << "\nDebug:destrList " << this->elemValue << "\n";
}

int List::length()
{
    List* current = this;
    int counter = 1;
    while(current->next)
    {
        current = current->next;
        counter++;
    }
    return counter;
}

void List::addValue(int value)
{
    List* current = this;
    while(current->next)
    {
        current = current->next;
    }
    current->next = new List(value);
}

void List::addPos(int pos, int value)
{
    List* current = this;
    if (pos >= this->length())
    {
        this->addValue(value);
    }
    else
    {
        while (current->next && (pos - 1))
        {
            current = current->next;
            pos--;
        }
        List* next = current->next;
        current->next = new List(value);
        current->next->next = next;
    }
}

void List::deletePos(int pos)
{
    List* current = this;
    List* previous = this;
    while(current->next && (pos - 1))
    {
        previous = current;
        current = current->next;
        pos--;
    }
    if (current->next)
    {
        List* next = current->next->next;
        delete current->next;
        current->next = next;
    }
    else
    {
        previous->next = nullptr;
        delete current;
    }
}

void List::deleteList()
{
    while (next)
    {
        List* deleted = next;
        next = next->next;
        delete deleted;
    }
}

void List::print()
{
    List* current = this;
    std::cout << "output:" << current->elemValue;
    while (current->next)
    {
        current = current->next;
        std::cout << "->" << current->elemValue;
    }
    std::cout << "\n";
}
