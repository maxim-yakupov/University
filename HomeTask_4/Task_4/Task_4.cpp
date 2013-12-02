#include "stdio.h"
#include "stack.h"

using namespace std;
using namespace StackModule;

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
    CharStack* polishInStack = createCharStack();
    CharStack* myOpsStack = createCharStack();
    int counter = strlen(incomeStr);
    while (counter != 0)
    {
        char token = incomeStr[0];
        if (isNumber(token))
        {
            push(polishInStack, token);
        }
        else if (isOpenBrace(token))
        {
            push(myOpsStack, token);
        }
        else if (isCloseBrace(token))
        {
            while (top(myOpsStack) != '(')
            {
                push(polishInStack, top(myOpsStack));
                pop(myOpsStack);
            };
            pop(myOpsStack);
        }
        else if (isOperator(token))
        {
            while ((myOpsStack->head != nullptr) && isOperator(myOpsStack->head->value) && (priority(token) <= priority(top(myOpsStack))))
            {
                push(polishInStack, top(myOpsStack));
                pop(myOpsStack);
            };
            push(myOpsStack, token);
        }
        else
        {
            break;
        };
        incomeStr = incomeStr + 1;
        counter--;
    };
    while (myOpsStack->head != nullptr)
    {
        push(polishInStack, top(myOpsStack));
        pop(myOpsStack);
    };

    delete myOpsStack;

    return polishInStack;
}

double compute(CharStack* polishInStack)
{
    CharStack* p = invertStack(polishInStack);
    delete polishInStack;
    polishInStack = p;

    Stack* myStack = create();
    while (polishInStack->head != nullptr)
    {
        if (isNumber(top(polishInStack)))
        {
            push(myStack, top(polishInStack) - '0');
        }
        else if (isOperator(top(polishInStack)))
        {
            push(myStack, makeOperation(top(polishInStack), myStack));
        }
        else
        {
            break;
        };
        pop(polishInStack);
    };
    double result = top(myStack);
    pop(myStack);
    delete myStack;
    delete p;
    return result;
}

CharStack* invertStack(CharStack* stack)
{
    CharStack* newStack = new CharStack {nullptr};
    while (stack->head != nullptr)
    {
        push(newStack, top(stack));
        pop(stack);
    };
    return newStack;
}

double makeOperation(char c, Stack* stack)
{
    double secondOperand = top(stack);
    pop(stack);
    double firstOperand = top(stack);
    pop(stack);
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
