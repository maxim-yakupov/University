#pragma once

namespace StackModule
{
    struct StackElement
    {
        StackElement* prev;
        double value;
    };

    struct CharStackElement
    {
        CharStackElement* prev;
        char value;
    };

    struct Stack
    {
        StackElement* head;
    };

    struct CharStack
    {
        CharStackElement* head;
    };

//prototypes of functions for stack of numbers
    Stack* create();

    void push(Stack* stack, double value);

    double top(Stack* stack);

    void pop(Stack* stack);
//prototypes of functions for stack of chars
    CharStack* createCharStack();

    void push(CharStack* stack, char value);

    char top(CharStack* stack);

    void pop(CharStack* stack);
}
