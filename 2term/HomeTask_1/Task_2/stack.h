#pragma once

template <class Type>
class Stack
{
public:
    Stack(){}
    virtual ~Stack(){}
    virtual void push(Type value) = 0;
    virtual Type top() const = 0;
    virtual void pop() = 0;
    virtual bool isEmpty() const = 0;
};
