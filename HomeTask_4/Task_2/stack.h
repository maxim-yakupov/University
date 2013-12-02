#pragma once

namespace StackModule
{
    struct StackElement
    {
        StackElement* prev;
        char value;
    };

    struct Stack
    {
        StackElement* head;
    };
//prototypes of functions
    Stack* create();

    void push(Stack* stack, char value);

    char top(Stack* stack);

    void pop(Stack* stack);
}
