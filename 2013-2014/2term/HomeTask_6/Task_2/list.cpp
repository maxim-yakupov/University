#include "list.h"
#include <iostream>

List::List() : head(nullptr), size(0)
{
}

List::~List()
{
}

unsigned int List::length()
{
    return this->size;
}

void List::print()
{
    ListElement* current = this->head;
    if (current)
    {
        std::cout << "output:" << current->elemValue;
        while (current->next)
        {
            current = current->next;
            std::cout << "->" << current->elemValue;
        }
    }
    std::cout << "\n";
}
