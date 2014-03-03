#pragma once
#include "stack.h"

template <class Type>
class PointerStack:public Stack<Type>
{
public:
    PointerStack();
    ~PointerStack();
    void push(Type value);
    Type top() const;
    void pop();
    bool isEmpty() const;
private:
    struct StackElement
    {
        StackElement* prev;
        Type value;
    };
    StackElement* head;
};

/*
 * Implementashion of PointerStack
 * (cause if I use derivement from template class,
 *  implementation should be in header file)
 */

template <class Type>
PointerStack<Type>::PointerStack()
{
    this->head = nullptr;
}

template <class Type>
PointerStack<Type>::~PointerStack()
{
    while (this->head)
    {
        this->pop();
    }
}

template <class Type>
void PointerStack<Type>::push(Type value)
{
    StackElement* newEl = new StackElement {this->head, value};
    this->head = newEl;
}

template <class Type>
Type PointerStack<Type>::top() const
{
    return this->head->value;
}

template <class Type>
void PointerStack<Type>::pop()
{
    StackElement* newEl = this->head;
    this->head = newEl->prev;
    delete newEl;
}

template <class Type>
bool PointerStack<Type>::isEmpty() const
{
    return this->head;
}
