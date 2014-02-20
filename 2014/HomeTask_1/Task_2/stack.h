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
//-----------
//namespace StackModule
//{
//    struct StackElement
//    {
//        StackElement* prev;
//        double value;
//    };

//    struct CharStackElement
//    {
//        CharStackElement* prev;
//        char value;
//    };

//    struct Stack
//    {
//        StackElement* head;
//    };

//    struct CharStack
//    {
//        CharStackElement* head;
//    };

//prototypes of functions for stack of numbers
//    Stack* create();

//    void push(Stack* stack, double value);

//    double top(Stack* stack);

//    void pop(Stack* stack);
////prototypes of functions for stack of chars
//    CharStack* createCharStack();

//    void push(CharStack* stack, char value);

//    char top(CharStack* stack);

//    void pop(CharStack* stack);
//}

