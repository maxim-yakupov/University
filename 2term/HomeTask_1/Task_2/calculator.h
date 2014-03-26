#pragma once

/**
 * @brief The TokenStruct struct
 */
struct TokenStruct
{
    /**
     * @brief value
     */
    double value;
    /**
     * @brief tokenTypeId
     * @detailed Saves code of token's type:
     * 0 - double
     * 1 - '+'
     * 2 - '-'
     * 3 - '*'
     * 4 - '/'
     * 5 - '('
     * 9 - some error
     */
    unsigned int tokenTypeId;
};

#include "pointerstack.h"
#include "arraystack.h"

#include <iostream>

template <class TTokenStack, class TDoubleStack>
/**
 * @brief The Calculator class
 */
class Calculator
{
public:
    /**
     * @brief operator () Changes string-expression(incomeStr field)
     * @param inStr String, which we copy in class
     */
    void operator()(char* inStr);
    /**
     * @brief Calculator
     */
    Calculator();
    /**
     * @brief Calculator Constructor with string-expression as parameter
     * @param incomeStr String, which we copy in class
     */
    Calculator(char* incomeStr);
    /**
     * @brief ~Calculator
     */
    ~Calculator();
    /**
     * @brief compute Evaluetes expression, which we inserted
     * @return Result of evaluation of string-expression(from field incomeStr)
     */
    double compute();
private:
    char* incomeStr;
    TTokenStack* polishInStack;

    int strlen(char* str);
    void makePolishNotation();
    void invertStack();
    bool isOperator(char c);
    bool isNumber(char c);
    double makeOperationById(unsigned int c, TDoubleStack* stack);
    bool isOperatorById(unsigned int c);
    bool isNumberById(unsigned int c);
    bool isOpenBrace(char c);
    bool isCloseBrace(char c);
    int priority(char c);
    int priorityById(unsigned int c);
};

/*
 * Implementashion of Calculator
 * (cause if I use derivement from template class,
 *  implementation should be in header file)
 */

template <class TTokenStack, class TDoubleStack>
void Calculator<TTokenStack, TDoubleStack>::operator()(char* inStr)
{
    unsigned int pos = 0;
    unsigned int length = strlen(inStr);
    delete [] incomeStr;
    incomeStr = new char[length + 1];
    while (length)
    {
        incomeStr[pos] = inStr[pos];
        ++pos;
        --length;
    }
    incomeStr[pos] = '\0';
}

template <class TTokenStack, class TDoubleStack>
Calculator<TTokenStack, TDoubleStack>::Calculator()
{
    incomeStr = new char{'\0'};
    polishInStack = new TTokenStack();
}

template <class TTokenStack, class TDoubleStack>
Calculator<TTokenStack, TDoubleStack>::Calculator(char* inStr)
{
    this->operator()(inStr);
    polishInStack = new TTokenStack();
}

template <class TTokenStack, class TDoubleStack>
Calculator<TTokenStack, TDoubleStack>::~Calculator()
{
    delete [] incomeStr;
    delete polishInStack;
}

template <class TTokenStack, class TDoubleStack>
int Calculator<TTokenStack, TDoubleStack>::strlen(char* str)
{
    int length = 0;
    while (*(str + length) != '\0')
    {
        length++;
    };
    return length;
}

template <class TTokenStack, class TDoubleStack>
void Calculator<TTokenStack, TDoubleStack>::makePolishNotation()
{
    TTokenStack* myOpsStack = new TTokenStack();
    int counter = strlen(incomeStr);
    int length = counter;
    unsigned int dotOccures = 0;
    double mult = 0.1;
    bool newNumber = true;
    while (counter != 0)
    {
        char letter = incomeStr[0];
        if (isNumber(letter) || letter == '.')
        {
            if (!polishInStack->isEmpty() || newNumber)
            {
                polishInStack->push({0, 0});
            }
            newNumber = false;
            if (isNumber(letter))
            {
                double topOfPolishStack = polishInStack->top().value;
                polishInStack->pop();
                if (!dotOccures)
                {
                    topOfPolishStack = topOfPolishStack * 10 + (letter - '0');
                }
                else
                {
                    topOfPolishStack = topOfPolishStack + (letter - '0') * mult;
                    mult /= 10;
                    dotOccures++;
                }
                polishInStack->push({topOfPolishStack, 0});
            }
            else
            {
                dotOccures++;
            }
        }
        else if (isOpenBrace(letter))
        {
            newNumber = true;
            mult = 0.1;
            dotOccures = 0;
            myOpsStack->push({letter, 5});
        }
        else if (isCloseBrace(letter))
        {
            newNumber = true;
            mult = 0.1;
            dotOccures = 0;
            while (myOpsStack->top().tokenTypeId != 5)//(
            {
                polishInStack->push(myOpsStack->top());
                myOpsStack->pop();
            };
            myOpsStack->pop();
        }
        else if (isOperator(letter))
        {
            newNumber = true;
            mult = 0.1;
            dotOccures = 0;
            while ((myOpsStack->isEmpty()) && isOperatorById(myOpsStack->top().tokenTypeId) && (priority(letter) <= priorityById(myOpsStack->top().tokenTypeId)))
            {
                polishInStack->push(myOpsStack->top());
                myOpsStack->pop();
            };
            unsigned int tokenId = 0;
            if (letter == '+')
            {
                tokenId = 1;
            }
            else if (letter == '-')
            {
                tokenId = 2;
            }
            else if (letter == '*')
            {
                tokenId = 3;;
            }
            else if (letter == '/')
            {
                tokenId = 4;
            }
            else
                tokenId = 9;
            myOpsStack->push({letter, tokenId});
        }
        else
        {
            newNumber = true;
                        mult = 0.1;
                        dotOccures = 0;
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
    incomeStr -= length;
    delete myOpsStack;
}

template <class TTokenStack, class TDoubleStack>
double Calculator<TTokenStack, TDoubleStack>::compute()
{
    makePolishNotation();
    invertStack();
    TDoubleStack* myStack = new TDoubleStack();
    myStack->push(0);
    while (polishInStack->isEmpty())
    {
        if (isNumberById(polishInStack->top().tokenTypeId))
        {
            myStack->push(polishInStack->top().value);
        }
        else if (isOperatorById(polishInStack->top().tokenTypeId))
        {
            myStack->push(makeOperationById(polishInStack->top().tokenTypeId, myStack));
        }
        else
        {
            break;
        };
        polishInStack->pop();
    };
    double result = myStack->top();
    delete myStack;
    polishInStack->clear();
    return result;
}

template <class TTokenStack, class TDoubleStack>
void Calculator<TTokenStack, TDoubleStack>::invertStack()
{
    TTokenStack* newStack = new TTokenStack();
    while (polishInStack->isEmpty())
    {
        newStack->push(polishInStack->top());
        polishInStack->pop();
    };
    delete polishInStack;
    polishInStack = newStack;
}

template <class TTokenStack, class TDoubleStack>
double Calculator<TTokenStack, TDoubleStack>::makeOperationById(unsigned int c, TDoubleStack* stack)
{
    double secondOperand = stack->top();
    stack->pop();
    double firstOperand = stack->top();
    stack->pop();
    switch (c) {
    case 1:
    {
        return firstOperand + secondOperand;
    };
    case 2:
    {
        return firstOperand - secondOperand;
    };
    case 3:
    {
        return firstOperand * secondOperand;
    };
    case 4:
    {
        return firstOperand / secondOperand;
    };
    default:
        return -1;
    }
}

template <class TTokenStack, class TDoubleStack>
bool Calculator<TTokenStack, TDoubleStack>::isOperator(char c)
{
    return ((c == '+') || (c == '-') || (c == '/') || (c == '*'));
}

template <class TTokenStack, class TDoubleStack>
bool Calculator<TTokenStack, TDoubleStack>::isOperatorById(unsigned int c)
{
    return (c >= 1) && (c <=4);
}

template <class TTokenStack, class TDoubleStack>
bool Calculator<TTokenStack, TDoubleStack>::isNumber(char c)
{
    return (c >= '0' && c <= '9');
}

template <class TTokenStack, class TDoubleStack>
bool Calculator<TTokenStack, TDoubleStack>::isNumberById(unsigned int c)
{
    return !c;
}

template <class TTokenStack, class TDoubleStack>
bool Calculator<TTokenStack, TDoubleStack>::isOpenBrace(char c)
{
    return (c == '(');
}

template <class TTokenStack, class TDoubleStack>
bool Calculator<TTokenStack, TDoubleStack>::isCloseBrace(char c)
{
    return (c == ')');
}

template <class TTokenStack, class TDoubleStack>
int Calculator<TTokenStack, TDoubleStack>::priority(char c)
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

template <class TTokenStack, class TDoubleStack>
int Calculator<TTokenStack, TDoubleStack>::priorityById(unsigned int c)
{
    switch(c)
    {
        case 3: return 3;
        case 4: return 3;

        case 1: return 2;
        case 2: return 2;
    }
    return 0;
}
