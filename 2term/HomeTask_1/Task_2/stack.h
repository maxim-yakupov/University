#pragma once

class Stack
{
public:
    Stack();
    ~Stack();
    void push(double value);
    double top() const;
    void pop();
    bool isEmpty() const;
private:
    struct StackElement
    {
        StackElement* prev;
        double value;
    };
    StackElement* head;
};

class CharStack
{
public:
    CharStack();
    ~CharStack();
    void push(char value);
    char top() const;
    void pop();
    bool isEmpty() const;
private:
    struct CharStackElement
    {
        CharStackElement* prev;
        char value;
    };
    CharStackElement* head;
};

