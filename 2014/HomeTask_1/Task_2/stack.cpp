#include "stack.h"

Stack::Stack()
{
    head = nullptr;
}

Stack::~Stack()
{
    while (head)
    {
        this->pop();
    }
}

void Stack::push(double value)
{
    StackElement* newEl = new StackElement {this->head, value};
    this->head = newEl;
}

double Stack::top() const
{
    return this->head->value;
}

void Stack::pop()
{
    StackElement* newEl = this->head;
    this->head = newEl->prev;
    delete newEl;
}

bool Stack::isEmpty() const
{
    return head;
}

//----------

CharStack::CharStack()
{
    head = nullptr;
}

CharStack::~CharStack()
{
    while (head)
    {
        this->pop();
    }
}

void CharStack::push(char value)
{
    CharStackElement* newEl = new CharStackElement {this->head, value};
    this->head = newEl;
}

char CharStack::top() const
{
    return this->head->value;
}

void CharStack::pop()
{
    CharStackElement* newEl = this->head;
    this->head = newEl->prev;
    delete newEl;
}

bool CharStack::isEmpty() const
{
    return head;
}
