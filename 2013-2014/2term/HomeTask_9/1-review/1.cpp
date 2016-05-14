#include <iostream>
#include "list.h"

using namespace std;

int main()
{
	DoubleList *list = new DoubleList;
	list->addElement(5);
	list->addElement(7);
	list->deleteElement(7);
	cout << list->getHead()->getNext()->getValue();
	delete list;
}
