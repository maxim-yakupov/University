#include <iostream>
#include <Windows.h>//sleep
#include "list.h"
#include "doublylinkedlist.h"

using namespace std;

int main()
{
    Sleep(300);//for debug(sometimes occures mistake of debugger without Sleep();)

    cout << "Singly linked list:\n";
    List list(0);
    list.addValue(2);
    list.addPos(5, 4);
    list.addPos(1, 99);
    list.deletePos(1);
    list.print();
    list.deleteList();
    list.print();

    cout << "\nDoubly linked list:\n";
    DoublyLinkedList list2(0);
    list2.addValue(2);
    list2.addPos(5, 4);
    list2.addPos(1, 99);
    list2.deletePos(1);
    list2.print();
    list2.deleteList();
    list2.print();

    cout << "\nSingly linked list heap try:\n";
    List* listH1 = new List(0);
    listH1->addValue(3);
    listH1->addValue(5);
    listH1->addValue(7);
    listH1->addPos(1, 2);
    listH1->print();
    listH1->deleteList();
    listH1->print();
    delete listH1;

    cout << "\nDoubly linked list heap try:\n";
    DoublyLinkedList* listH2 = new DoublyLinkedList(0);
    listH2->addValue(3);
    listH2->addValue(5);
    listH2->addValue(7);
    listH2->addPos(1, 2);
    listH2->print();
    listH2->deleteList();
    listH2->print();
    delete listH2;

    return 0;
}
