#include "cycled_lists_mod.h"

//прототипы вспомогательных функций

//функции для работы со списками
namespace cycled_lists
{
    CycledList* initCycledList(int value)
    {
        ListElement* newElem = new ListElement {value, nullptr};
        newElem->next = newElem;
        return new CycledList {newElem, 1};
    }

    void addElement(ListElement* prev, int value, CycledList* list)
    {
        ListElement* newElem = new ListElement {value, prev->next};
        prev->next = newElem;
        list->amount++;
    }

    void deleteList(CycledList* list)
    {
        while (list->amount != 0)
        {
            deleteElement(list->head, list);
        };
        delete list;
    }

    void deleteElement(ListElement* prevEl, CycledList* list)
    {
        ListElement* newElem = prevEl->next;
        prevEl->next = newElem->next;
        if (list->head == newElem)
        {
            list->head = newElem->next;
        };
        delete newElem;
        list->amount--;
    }
}
