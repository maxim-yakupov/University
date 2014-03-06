#pragma once
#include "pointerstack.h"
#include "arraystack.h"

template <class TCharStack, class TDoubleStack>
class Calculator
{
public:
    Calculator(char* incomeStr);
    ~Calculator();
    double compute();
private:
    char* incomeStr;
    TCharStack* polishInStack;

    int strlen(char* str);
    void makePolishNotation();
    void invertStack();
    double makeOperation(char c, TDoubleStack* stack);
    bool isOperator(char c);
    bool isNumber(char c);
    bool isOpenBrace(char c);
    bool isCloseBrace(char c);
    int priority(char c);
};

/*
 * Implementashion of Calculator
 * (cause if I use derivement from template class,
 *  implementation should be in header file)
 */

template <class TCharStack, class TDoubleStack>
Calculator<TCharStack, TDoubleStack>::Calculator(char* incomeStr)
{
    unsigned int pos = 0;
    unsigned int length = this->strlen(incomeStr);
    this->incomeStr = new char[length];
    while (length)
    {
        this->incomeStr[pos] = incomeStr[pos];
        ++pos;
        --length;
    }
    this->polishInStack = new TCharStack();
}

template <class TCharStack, class TDoubleStack>
Calculator<TCharStack, TDoubleStack>::~Calculator()
{
    delete [] incomeStr;
    delete polishInStack;
}

template <class TCharStack, class TDoubleStack>
int Calculator<TCharStack, TDoubleStack>::strlen(char* str)
{
    int length = 0;
    while (*(str + length) != '\0')
    {
        length++;
    };
    return length;
}

template <class TCharStack, class TDoubleStack>
void Calculator<TCharStack, TDoubleStack>::makePolishNotation()
{
    TCharStack* myOpsStack = new TCharStack();
    int counter = strlen(incomeStr);
    while (counter != 0)
    {
        char token = incomeStr[0];
        if (isNumber(token))
        {
            polishInStack->push(token);
        }
        else if (isOpenBrace(token))
        {
            myOpsStack->push(token);
        }
        else if (isCloseBrace(token))
        {
            while (myOpsStack->top() != '(')
            {
                polishInStack->push(myOpsStack->top());
                myOpsStack->pop();
            };
            myOpsStack->pop();
        }
        else if (isOperator(token))
        {
            while ((myOpsStack->isEmpty()) && isOperator(myOpsStack->top()) && (priority(token) <= priority(myOpsStack->top())))
            {
                polishInStack->push(myOpsStack->top());
                myOpsStack->pop();
            };
            myOpsStack->push(token);
        }
        else
        {
            break;
        };
        incomeStr = incomeStr + 1;
        counter--;
    };
    while (myOpsStack->isEmpty())
    {
        polishInStack->push(myOpsStack->top());
        myOpsStack->pop();
    };

    delete myOpsStack;
}

template <class TCharStack, class TDoubleStack>
double Calculator<TCharStack, TDoubleStack>::compute()
{
    makePolishNotation();
    invertStack();
    TDoubleStack* myStack = new TDoubleStack();
    while (polishInStack->isEmpty())
    {
        if (isNumber(polishInStack->top()))
        {
            myStack->push(polishInStack->top() - '0');
        }
        else if (isOperator(polishInStack->top()))
        {
            myStack->push(makeOperation(polishInStack->top(), myStack));
        }
        else
        {
            break;
        };
        polishInStack->pop();
    };
    double result = myStack->top();
    delete myStack;
    delete polishInStack;
    return result;
}

template <class TCharStack, class TDoubleStack>
void Calculator<TCharStack, TDoubleStack>::invertStack()
{
    TCharStack* newStack = new TCharStack();
    while (polishInStack->isEmpty())
    {
        newStack->push(polishInStack->top());
        polishInStack->pop();
    };
    delete polishInStack;
    polishInStack = newStack;
}

template <class TCharStack, class TDoubleStack>
double Calculator<TCharStack, TDoubleStack>::makeOperation(char c, TDoubleStack* stack)
{
    double secondOperand = stack->top();
    stack->pop();
    double firstOperand = stack->top();
    stack->pop();
    switch (c) {
    case '+':
    {
        return firstOperand + secondOperand;
    };
    case '-':
    {
        return firstOperand - secondOperand;
    };
    case '*':
    {
        return firstOperand * secondOperand;
    };
    case '/':
    {
        return firstOperand / secondOperand;
    };
    default:
        return -1;
    }
}

template <class TCharStack, class TDoubleStack>
bool Calculator<TCharStack, TDoubleStack>::isOperator(char c)
{
    return ((c == '+') || (c == '-') || (c == '/') || (c == '*'));
}

template <class TCharStack, class TDoubleStack>
bool Calculator<TCharStack, TDoubleStack>::isNumber(char c)
{
    return (c >= '0' && c <= '9');
}

template <class TCharStack, class TDoubleStack>
bool Calculator<TCharStack, TDoubleStack>::isOpenBrace(char c)
{
    return (c == '(');
}

template <class TCharStack, class TDoubleStack>
bool Calculator<TCharStack, TDoubleStack>::isCloseBrace(char c)
{
    return (c == ')');
}

template <class TCharStack, class TDoubleStack>
int Calculator<TCharStack, TDoubleStack>::priority(char c)
{
    switch(c)
    {
        case '*': return 3;
        case '/': return 3;

        case '+': return 2;
        case '-': return 2;
    }
    return 0;
}
