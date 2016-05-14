#include "stdio.h"
#include "stack.h"

using namespace std;
using namespace StackModule;

bool isOperator(char c);
bool isNumber(char c);

double makeOperation(char c, Stack* stack);

int main()
{
    Stack* myStack = create();
    printf("Write expression in polish notation: ");
    char token = '\0';
    while (scanf("%c", &token))
    {
        if (isNumber(token))
        {
            push(myStack, token - '0');
        }
        else if (isOperator(token))
        {
            push(myStack, makeOperation(token, myStack));
        }
        else
        {
            break;
        };
    };
    printf("Result: %f", myStack->head->value);

    pop(myStack);
    delete myStack;
    return 0;
}

bool isOperator(char c)
{
    return ((c == '+') || (c == '-') || (c == '/') || (c == '*'));
}

bool isNumber(char c)
{
    return (c >= '0' && c <= '9');
}

double makeOperation(char c, Stack* stack)
{
    int secondOperand = top(stack);
    pop(stack);
    int firstOperand = top(stack);
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
