#pragma once
#include "stack.h"

template <class Type>
class ArrayStack:public Stack<Type>
{
public:
    ArrayStack<Type>();
    ~ArrayStack<Type>();
    void push(Type value);
    Type top() const;
    void pop();
    bool isEmpty() const;
private:
    Type array[1000];
    unsigned int head;
};

/*
 *
 *
 *
 *
 * Implementashion of ArrayStack
 * (cause if I use derivement from template class,
 *  implementashion should be in header file)
 */

template <class Type>
ArrayStack<Type>::ArrayStack()
{
    this->head = 0;
}

template <class Type>
ArrayStack<Type>::~ArrayStack()
{
    while (this->head)
    {
        this->pop();
    }
}

template <class Type>
void ArrayStack<Type>::push(Type value)
{
    this->array[this->head] = value;
    this->head++;
}

template <class Type>
Type ArrayStack<Type>::top() const
{
    return this->array[this->head - 1];
}

template <class Type>
void ArrayStack<Type>::pop()
{
    this->head--;
}

template <class Type>
bool ArrayStack<Type>::isEmpty() const
{
    return this->head;
}
