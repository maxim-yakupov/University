#include "stack.h"

namespace StackModule
{
    Stack* create()
    {
        return new Stack {nullptr};
    }

    void push(Stack* stack, double value)
    {
        StackElement* newEl = new StackElement {stack->head, value};
        stack->head = newEl;
    }

    double top(Stack* stack)
    {
        return stack->head->value;
    }

    void pop(Stack* stack)
    {
        StackElement* newEl = stack->head;
        stack->head = newEl->prev;
        delete newEl;
    }

    //---for stack of chars
    CharStack* createCharStack()
    {
        return new CharStack {nullptr};
    }

    void push(CharStack* stack, char value)
    {
        CharStackElement* newEl = new CharStackElement {stack->head, value};
        stack->head = newEl;
    }

    char top(CharStack* stack)
    {
        return stack->head->value;
    }

    void pop(CharStack* stack)
    {
        CharStackElement* newEl = stack->head;
        stack->head = newEl->prev;
        delete newEl;
    }
}
