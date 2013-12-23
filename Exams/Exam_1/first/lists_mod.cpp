#include "lists_mod.h"

//прототипы вспомогательных функций
lists::ListElement* goSomeSteps(int pos, lists::List* list);

//функции для работы со списками
namespace lists
{
    List* initList(int value)
    {
        return new List {new ListElement {value, nullptr}, 0};
    }

    ListElement* getElement(int pos, List* list)
    {
        return goSomeSteps(pos, list);
    }

    void addElement(ListElement* prev, int value, List* list)
    {
        ListElement* newElem = new ListElement {value, prev->next};
        prev->next = newElem;
        list->length++;
    }

    void deleteElement(ListElement* prev, List* list)
    {
        ListElement* newElem = prev->next;
        prev->next = newElem->next;
        delete newElem;
        list->length--;
    }

    void deleteList(List* list)
    {
        while (list->length != 0)
        {
            deleteElement(getElement(0, list), list);
        };
        delete list->head;
        delete list;
    }
}

//вспомогательные функции
lists::ListElement* goSomeSteps(int pos, lists::List *list)
{
    int counter = 0;
    lists::ListElement* current = list->head;
    while (counter < pos)
    {
        current = current->next;
        counter++;
    };
    return current;
}
