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
    void clear();
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
ArrayStack<Type>::ArrayStack() : head(0)
{
}

template <class Type>
ArrayStack<Type>::~ArrayStack()
{
    clear();
}

template <class Type>
void ArrayStack<Type>::push(Type value)
{
    array[head] = value;
    head++;
}

template <class Type>
Type ArrayStack<Type>::top() const
{
    return array[head - 1];
}

template <class Type>
void ArrayStack<Type>::pop()
{
    if (head) head--;
}

template <class Type>
bool ArrayStack<Type>::isEmpty() const
{
    return head;
}

template <class Type>
void ArrayStack<Type>::clear()
{
    while (head)
    {
        pop();
    }
}
