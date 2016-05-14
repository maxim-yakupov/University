#include "lists_mod.h"

//прототипы вспомогательных функций
ListElement* goSomeSteps(int pos, List list);

//функции для работы со списками
namespace lists_mod
{

    ListElement addElem_get(int pos, int value, List list)
    {
        ListElement* current = goSomeSteps(pos - 1, list);
        ListElement* newElem = new ListElement{value, current -> next};
        current -> next = newElem;
        return *newElem;
    }

    ListElement* getElem(int pos, List list)
    {
        return goSomeSteps(pos, list);
    }

    void addElem(int pos, int value, List list)
    {
        ListElement* current = goSomeSteps(pos - 1, list);
        ListElement* newElem = new ListElement{value, current -> next};
        current -> next = newElem;
    }

    void delElem(int pos, List list)
    {
        ListElement* current = goSomeSteps(pos - 1, list);
        ListElement* newElem = current -> next;
        current -> next = newElem -> next;
        delete newElem;
    }
}

//вспомогательные функции
ListElement* goSomeSteps(int pos, List list)
{
    int counter = 0;
    ListElement* current = list.head;
    while (counter < pos)
    {
        current = current -> next;
        counter++;
    };
    return current;
}
