#include "stdio.h"
#include "stack.h"

using namespace std;
using namespace StackModule;

bool isOperator(char c);

bool isNumber(char c);

bool isOpenBrace(char c);

bool isCloseBrace(char c);

int priority(char c);

int main()
{
    Stack* myStack = create();
    printf("Write expression: ");
    char token = '\0';
    while (scanf("%c", &token))
    {
        if (isNumber(token))
        {
            printf("%c", token);
        }
        else if (isOpenBrace(token))
        {
            push(myStack, token);
        }
        else if (isCloseBrace(token))
        {
            while (top(myStack) != '(')
            {
                printf("%c", top(myStack));
                pop(myStack);
            };
            pop(myStack);
        }
        else if (isOperator(token))
        {
            while ((myStack->head != nullptr) && isOperator(myStack->head->value) && (priority(token) <= priority(top(myStack))))
            {
                printf("%c", top(myStack));
                pop(myStack);
            };
            push(myStack, token);
        }
        else
        {
            break;
        };
    };
    while (myStack->head != nullptr)
    {
        printf("%c", top(myStack));
        pop(myStack);
    };
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
