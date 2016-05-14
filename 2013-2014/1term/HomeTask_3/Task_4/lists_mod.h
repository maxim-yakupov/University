#pragma once

namespace lists
{
    struct ListElement
    {
        int value;
        ListElement* next;
    };
    struct List
    {
        ListElement* head;
        int length;
    };
    List* initList(int value);
    ListElement* getElement(int pos, List *list);
    void addElement(ListElement* prev, int value, List* list);
    void deleteElement(ListElement *prev, List *list);
    void deleteList(List *list);
}

