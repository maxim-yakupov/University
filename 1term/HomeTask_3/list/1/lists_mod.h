#pragma once

struct ListElement
{
    int value;
    ListElement* next;
};

struct List
{
    ListElement* head;
};

namespace lists_mod
{
    ListElement addElem_get(int pos, int value, List list);
    ListElement* getElem(int pos, List list);
    void addElem(int pos, int value, List list);
    void delElem(int pos, List list);
}

