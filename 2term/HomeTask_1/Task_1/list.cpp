#include "list.h"
#include <iostream>

List::List() : head(nullptr), size(0)
{
//    std::cout << "\nDebug:constrList " << this->elemValue << "\n";
}

List::~List()
{
    //    std::cout << "\nDebug:destrList " << this->elemValue << "\n";
}

//commented, cause you said, that it is unnesessary :(
//ListElement *List::getPos(int pos)
//{
//    ListElement* current = this->head;
//    while (pos && current->next)
//    {
//        current = current->next;
//        pos--;
//    }
//    return current;
//}

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
