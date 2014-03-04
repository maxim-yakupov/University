#include "singlylinkedlist.h"
//#include <iostream>

SinglyLinkedList::SinglyLinkedList()
{
//    std::cout << "\nDebug:constrSLList " << this->elemValue << "\n";
}

SinglyLinkedList::~SinglyLinkedList()
{
//    std::cout << "\nDebug:destrSLList " << this->elemValue << "\n";
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
        current->next = new SLListElement;//!!D:\Ucheba\Programming\2014\HomeTask_1\Task_1\singlylinkedlist.cpp:28: ошибка: could not convert '{value, nullptr}' from '<brace-enclosed initializer list>' to 'SLListElement' current->next = new SLListElement{value, nullptr};
    //                                                                                                                                                                                                                                                                       ^
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
}
