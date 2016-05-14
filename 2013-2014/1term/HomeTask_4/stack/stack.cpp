#include "stack.h"

namespace StackModule
{
    Stack* create()
    {
        return new Stack {nullptr};
    }
    void add(Stack* stack, int value)
    {
        StackElement* newEl = new StackElement {stack->head, value};
        stack->head = newEl;
    }
    int top(Stack* stack)
    {
        return stack->head->value;
    }
    void pop(Stack* stack)
    {
        StackElement* newEl = stack->head;
        stack->head = newEl->prev;
        delete newEl;
    }
}
