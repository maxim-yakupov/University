#include "stdio.h"
#include "stack.h"

using namespace std;
using namespace StackModule;

int main()
{
    Stack* myStack = create();
    add(myStack, 0);
    add(myStack, 1);
    pop(myStack);
    printf("%d", top(myStack));
    return 0;
}

