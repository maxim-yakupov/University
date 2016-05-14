#pragma once

namespace StackModule
{
    struct StackElement
    {
        StackElement* prev;
        int value;
    };
    struct Stack
    {
        StackElement* head;
    };
//prototypes of functions
    Stack* create();
    void add(Stack* stack, int value);
    int top(Stack* stack);
    void pop(Stack* stack);
}
