#pragma once

namespace cycled_lists
{
    struct ListElement
    {
        int value;
        ListElement* next;
    };
    struct CycledList
    {
        ListElement* head;
        int amount;
    };
    CycledList* initCycledList(int value);
    void addElement(ListElement* prev, int value, CycledList* list);
    void deleteList(CycledList *list);
    void deleteElement(ListElement* prevEl, CycledList *list);
}

