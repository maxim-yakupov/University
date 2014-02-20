#include "stdio.h"
#include "stack.h"

using namespace std;

int strlen(char* str);

CharStack* makePolishNotation(char* incomeStr);

double compute(CharStack* polishInStack);

CharStack *invertStack(CharStack *stack);

double makeOperation(char c, Stack* stack);

bool isOperator(char c);

bool isNumber(char c);

bool isOpenBrace(char c);

bool isCloseBrace(char c);

int priority(char c);

int main()
{
    printf("Write expression: ");
    char* incomeStr = new char[100];
    scanf("%s", incomeStr);
    //---making of polish notation from input string
    CharStack* polishInStack = makePolishNotation(incomeStr);
    delete [] incomeStr;
    //---computing
    double result = compute(polishInStack);
    printf("Result: %g", result);
    return 0;
}

int strlen(char* str)
{
    int length = 0;
    while (*(str + length) != '\0')
    {
        length++;
    };
    return length;
}

CharStack* makePolishNotation(char* incomeStr)
{
    CharStack* polishInStack = new CharStack();
    CharStack* myOpsStack = new CharStack();
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
            /*private head*/while ((myOpsStack->isEmpty()) && isOperator(myOpsStack->top()) && (priority(token) <= priority(myOpsStack->top())))
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
    /*private head*/while (myOpsStack->isEmpty())
    {
        polishInStack->push(myOpsStack->top());
        myOpsStack->pop();
    };

    delete myOpsStack;

    return polishInStack;
}

double compute(CharStack* polishInStack)
{
    CharStack* p = invertStack(polishInStack);
    delete polishInStack;
    polishInStack = p;

    Stack* myStack = new Stack();
    /*private head*/while (polishInStack->isEmpty())
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
    myStack->pop();
    delete myStack;
    delete p;
    return result;
}

CharStack* invertStack(CharStack* stack)
{
    CharStack* newStack = new CharStack();
    /*private head*/while (stack->isEmpty())
    {
        newStack->push(stack->top());
        stack->pop();
    };
    return newStack;
}

double makeOperation(char c, Stack* stack)
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

bool isOperator(char c)
{
    return ((c == '+') || (c == '-') || (c == '/') || (c == '*'));
}

bool isNumber(char c)
{
    return (c >= '0' && c <= '9');
}

bool isOpenBrace(char c)
{
    return (c == '(');
}

bool isCloseBrace(char c)
{
    return (c == ')');
}

int priority(char c)
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
