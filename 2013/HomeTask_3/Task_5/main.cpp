#include "stdio.h"
#include "cycled_lists_mod.h"

using namespace std;
using namespace cycled_lists;

int main()
{
    CycledList* myList = initCycledList(1);
    printf("Write number of mans in circle:");
    int n = 1;
    scanf("%d", &n);
    ListElement* current = myList->head;
    for (int i = 2; i <= n; i++)
    {
        addElement(current, i, myList);
        current = current->next;
    };
    printf("Write size of step:");
    int m = 1;
    scanf("%d", &m);
    current = myList->head;
    while (myList->amount != 1)
    {
        for (int i = 1; i < m - 1; i++)
        {
            current = current->next;
        };
        deleteElement(current, myList);
        current = current->next;
    };
    printf("Number of survivor is %d", myList->head->value);
    deleteList(myList);
    return 0;
}

