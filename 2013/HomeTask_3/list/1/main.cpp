#include <iostream>
#include "lists_mod.h"

using namespace std;
using namespace lists_mod;

int main()
{
    List myList = {nullptr};
    myList.head = new ListElement{0, nullptr};
    addElem(1, 1, myList);
    addElem(2, 2, myList);
    addElem(3, 3, myList);
    delElem(2, myList);
    getElem(1, myList)->value = 100;
    cout << getElem(1, myList)->value <<endl;
    return 0;
}

