#pragma once

template <class Type>
/**
 * @brief The Stack class
 * @detailed Template class of stack
 */
class Stack
{
public:
    /**
     * @brief Stack
     * @detailed Constructor of class Stack
     */
    Stack(){}
    /**
     * @brief ~Stack
     * @detailed Virtual destructor of class Stack
     */
    virtual ~Stack(){}
    /**
     * @brief push Puts value on the top of stack
     * @param value Value, which puts on the top of stack
     */
    virtual void push(Type value) = 0;
    /**
     * @brief top Returns value from the top of stack
     * @return Value of top element of stack
     */
    virtual Type top() const = 0;
    /**
     * @brief pop Removes top element from stack
     */
    virtual void pop() = 0;
    /**
     * @brief isEmpty Checks emptiness of stack
     * @return Returns 'true' if not empty, returns 'false' if stack is empty
     */
    virtual bool isEmpty() const = 0;
    /**
     * @brief clear Removes all elements of stack
     */
    virtual void clear() = 0;
};
