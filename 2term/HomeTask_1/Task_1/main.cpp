#include <iostream>
#include <unistd.h>//sleep
#include "singlylinkedlist.h"
#include "doublylinkedlist.h"

using namespace std;

int main()
{
    cout << "Wait a second";
    sleep(1);//for debug(sometimes occures mistake of debugger without sleep();)
    cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b";

    cout << "Singly linked list:\n";
    SinglyLinkedList list;
    list.addValue(2);
    list.addPos(5, 4);
    list.addPos(5, 3);
    list.addPos(1, 99);
    list.deletePos(1);
    list.print();

    cout << "\nDoubly linked list:\n";
    DoublyLinkedList list2;
    list2.addValue(2);
    list2.addPos(5, 4);
    list2.addPos(5, 3);
    list2.addPos(1, 99);
    list2.print();
    list2.deletePos(1);
    list2.print();

    cout << "\nSingly linked list heap try:\n";
    SinglyLinkedList* listH1 = new SinglyLinkedList();
    listH1->addValue(3);
    listH1->addValue(5);
    listH1->addValue(7);
    listH1->addPos(1, 2);
    listH1->print();
    delete listH1;

    cout << "\nDoubly linked list heap try:\n";
    DoublyLinkedList* listH2 = new DoublyLinkedList();
    listH2->addValue(3);
    listH2->addValue(5);
    listH2->addValue(7);
    listH2->addPos(1, 2);
    listH2->print();
    delete listH2;

    return 0;
}
