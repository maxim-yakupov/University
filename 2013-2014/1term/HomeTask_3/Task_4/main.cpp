#include "stdio.h"
#include "limits.h"
#include "lists_mod.h"

using namespace std;
using namespace lists;

void printList(int first, int length, List *list);

int main()
{
    List* myList = initList(- INT_MAX);
    int choice = 3;
    while (choice != 0)
    {
        printf("**************************************\n");
        printf("* 0 - exit                           *\n");
        printf("* 1 - add a value to sorted list     *\n");
        printf("* 2 - remove a value from sorted list*\n");
        printf("* 3 - print list                     *\n");
        printf("**************************************\n");
        printf("Write command:");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
            {
                printf("Enter value:");
                int value = 1;
                scanf("%d", &value);
                ListElement* current = getElement(0, myList);
                for (int i = 1; i <= myList->length; i++)
                {
                    if ((current->value < value) && (current->next->value >= value))//если value лежит между текущим и следующим
                    {
                        break;
                    };
                    current = current->next;
                };
                addElement(current, value, myList);
                break;
            };
            //
            case 2:
            {
                printf("Enter value:");
                int value = - INT_MAX;
                scanf("%d", &value);
                ListElement* current = getElement(0, myList);
                for (int i = 1; i <= myList->length; i++)
                {
                    if (current->next->value == value)
                    {
                        deleteElement(current, myList);
                        break;
                    }
                    else
                    {
                        current = current->next;
                    };
                };
                break;
            };
            //
            case 3:
            {
                printList(1, myList->length, myList);
                break;
            };
            default:
            {
                break;
            };
        };
    };
    deleteList(myList);
    return 0;
}

void printList(int first, int length, List* list)
{
    printf("=====\n");
    for (int i = first; i <= length; i++)
    {
        printf("%d\n",getElement(i, list)->value);
    };
    if (getElement(first, list) == nullptr)
    {
        printf("List is empty\n");
    };
    printf("=====\n");
}
