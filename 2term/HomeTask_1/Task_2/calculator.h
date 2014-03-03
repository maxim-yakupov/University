#pragma once
#include "pointerstack.h"
#include "arraystack.h"

template <class TCharStack, class TDoubleStack>
class Calculator
{
public:
    Calculator(char* incomeStr);
    double compute();
private:
    char* incomeStr;
    TCharStack* polishInStack;
    int strlen(char* str);
    void makePolishNotation();
    TCharStack *invertStack();
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
    this->incomeStr = incomeStr;
    this->polishInStack = new TCharStack();
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
    int counter = this->strlen(this->incomeStr);
    while (counter != 0)
    {
        char token = this->incomeStr[0];
        if (this->isNumber(token))
        {
            this->polishInStack->push(token);
        }
        else if (this->isOpenBrace(token))
        {
            myOpsStack->push(token);
        }
        else if (this->isCloseBrace(token))
        {
            while (myOpsStack->top() != '(')
            {
                this->polishInStack->push(myOpsStack->top());
                myOpsStack->pop();
            };
            myOpsStack->pop();
        }
        else if (this->isOperator(token))
        {
            while ((myOpsStack->isEmpty()) && isOperator(myOpsStack->top()) && (this->priority(token) <= this->priority(myOpsStack->top())))
            {
                this->polishInStack->push(myOpsStack->top());
                myOpsStack->pop();
            };
            myOpsStack->push(token);
        }
        else
        {
            break;
        };
        this->incomeStr = this->incomeStr + 1;
        counter--;
    };
    while (myOpsStack->isEmpty())
    {
        this->polishInStack->push(myOpsStack->top());
        myOpsStack->pop();
    };

    delete myOpsStack;
}

template <class TCharStack, class TDoubleStack>
double Calculator<TCharStack, TDoubleStack>::compute()
{
    this->makePolishNotation();
    TCharStack* p = this->invertStack();
    delete this->polishInStack;
    this->polishInStack = p;

    TDoubleStack* myStack = new TDoubleStack();
    while (this->polishInStack->isEmpty())
    {
        if (this->isNumber(this->polishInStack->top()))
        {
            myStack->push(this->polishInStack->top() - '0');
        }
        else if (this->isOperator(this->polishInStack->top()))
        {
            myStack->push(this->makeOperation(this->polishInStack->top(), myStack));
        }
        else
        {
            break;
        };
        this->polishInStack->pop();
    };
    double result = myStack->top();
    myStack->pop();
    delete myStack;
    delete p;
    return result;
}

template <class TCharStack, class TDoubleStack>
TCharStack *Calculator<TCharStack, TDoubleStack>::invertStack()
{
    TCharStack* newStack = new TCharStack();
    while (this->polishInStack->isEmpty())
    {
        newStack->push(this->polishInStack->top());
        this->polishInStack->pop();
    };
    return newStack;
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
