#include "stdio.h"
#include "lists_mod.h"
#include <limits.h>

using namespace std;

using namespace lists;

int main()
{
    printf("Write number of elements from Vasya's list: ");
    int vasyaLength;
    scanf("%d", &vasyaLength);
    printf("Write elements from Vasya's list: ");
    List* vasyaList = initList(INT_MAX);
    int value = 0;
    for (int i = 0; i < vasyaLength; i++)// n
    {
        scanf("%d", &value);
        addElement(getElement(vasyaList->length, vasyaList), value, vasyaList);
    }
    List* resultList = vasyaList;
    printf("Write number of elements from Petya's list: ");
    int petyaLength;
    scanf("%d", &petyaLength);
    printf("Write elements from Petya's list: ");
    for (int i = 0; i < petyaLength; i++)// n
    {
        scanf("%d", &value);
        ListElement* current = getElement(0, resultList);
        for (int i = 1; i <= resultList->length; i++) // n
        {
            if ((current->value > value) && (current->next->value <= value))//если value лежит между текущим и следующим
            {
                break;
            }
            current = current->next;
        }
        addElement(current, value, vasyaList);
    }
    printf("Result: ");
    while (resultList->length != 0)// n
    {
        printf("%d ", resultList->head->next->value);
        deleteElement(resultList->head, resultList);
    }
    delete resultList->head;
    deleteList(resultList);
    // n + n*n + n = n^2
    return 0;
}

