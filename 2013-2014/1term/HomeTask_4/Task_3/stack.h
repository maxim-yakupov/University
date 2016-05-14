#pragma once

namespace StackModule
{
    struct StackElement
    {
        StackElement* prev;
        double value;
    };

    struct Stack
    {
        StackElement* head;
    };
//prototypes of functions
    Stack* create();

    void push(Stack* stack, double value);

    char top(Stack* stack);

    void pop(Stack* stack);
}
