#include "stdio.h"
#include "stack.h"

using namespace std;

using namespace StackModule;

bool isOpenBracer(char token)
{
    if ((token == '(')||(token == '[')||(token == '{'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isCloseBracer(char token)
{
    if ((token == ')')||(token == ']')||(token == '}'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isPare(char token_1, char token_2)
{
    if (((token_1 == '(') && (token_2 == ')')) || ((token_1 == '[') && (token_2 == ']')) || ((token_1 == '{') && (token_2 == '}')))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    char token = '\0';
    Stack* bracersStack = create();
    printf("Write your string: ");
    while (scanf("%c", &token))
    {
        if ((token == '\r') || (token == '\n'))
        {
            break;
        }
        if (isOpenBracer(token))
        {
            push(bracersStack, token);
        }
        else if (isCloseBracer(token))
        {
            if (isPare(top(bracersStack), token))
            {
                pop(bracersStack);
            }
            else
            {
                break;
            }
        }
    }
    if (bracersStack->head == nullptr)
    {
        printf("\nIt's correct");
    }
    else
    {
        printf("\nIt's NOT correct");
    }
    while (bracersStack->head != nullptr)
    {
        pop(bracersStack);
    }
    delete bracersStack;
    return 0;
}

