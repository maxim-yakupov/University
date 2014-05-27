#include <stdio.h>
#include "plist.h"

PList::PList()
{
    head = new Node;
    head->next = NULL;
    head->value = 0;
}

PList::~PList()
{
    removeList();
    delete head;
}

int PList::length()
{
    return head->value;
}

void PList::add(int value, int num)
{
    if (num <= head->value)
    {
        int counter = 1;
        Node *prevNode = head;
        while (counter < num)
        {
            prevNode = prevNode->next;
            counter++;
        }
        Node *addingNode = new Node;
        addingNode->value = value;
        addingNode->next = prevNode->next;
        prevNode->next = addingNode;
        head->value++;
    }
    else
    {
        Node *prevNode = head;
        while (prevNode->next)
        {
            prevNode = prevNode->next;
        }
        Node *addingNode = new Node;
        addingNode->value = value;
        addingNode->next = prevNode->next;
        prevNode->next = addingNode;
        head->value++;
    }
}

void PList::del(int num)
{
    if ((num <= head->value) && (num > 0))
    {
        int counter = 1;
        Node *prevNode = head;
        while (counter < num)
        {
            prevNode = prevNode->next;
            counter++;
        }
        Node *addingNode = prevNode->next;
        prevNode->next = prevNode->next->next;
        delete addingNode;
        head->value--;
    }
}

void PList::removeList()
{
    while (head->next)
    {
        del(1);
    }
}

int PList::returnValue(int num)
{
    if ((num <= head->value) && (num > 0))
    {
        int counter = 1;
        Node *prevNode = head;
        while (counter < num)
        {
            prevNode = prevNode->next;
            counter++;
        }
        return prevNode->next->value;
    }
    else
    {
        return -32000;
    }
}

void PList::printList()
{
    Node *currentNode = head;
    while(currentNode->next)
    {
        currentNode = currentNode->next;
        printf("%i ", currentNode->value);
    }
}

void PList::swap(int i, int j)
{
    if ((i <= head->value) && (i > 0) && (j <= head->value) && (j > 0))
    {
        int counter = 1;
        Node *firstPrevNode = head;
        while (counter < i)
        {
            firstPrevNode = firstPrevNode->next;
            counter++;
        }
        counter = 1;
        Node *secondPrevNode = head;
        while (counter < j)
        {
            secondPrevNode = secondPrevNode->next;
            counter++;
        }
        int a = firstPrevNode->next->value;
        firstPrevNode->next->value = secondPrevNode->next->value;
        secondPrevNode->next->value = a;
    }
}
