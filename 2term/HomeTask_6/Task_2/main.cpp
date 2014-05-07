#include <iostream>
#include "uniquelist.h"
#include "testUniqueList.h"

using namespace std;

int main()
{
    //test
    TestUniqueList testUniqueList;
    QTest::qExec(&testUniqueList);
    //end test

    UniqueList list;
    char command = 'h';
    int input = 0;
    while (command != 'q')
    {
        switch (command) {
        case 'h':
            cout << "Commands list:\n";
            cout << "'h' - this help;\n";
            cout << "'a' - add value;\n";
            cout << "'d' - delete value;\n";
            cout << "'p' - print list;\n";
            cout << "'q' - end program.\n";
            break;
        case 'p':
            cout << "Your list:";
            list.print();
            break;
        case 'a':
            cout << "input>> ";
            cin >> input;
            try
            {
                list.addValue(input);
                cout << "Value added\n";
            }
            catch(Exceptions::AddsExistingValue &)
            {
                cout << "Error: Value already in this list";
            }
            break;
        case 'd':
            cout << "input>> ";
            cin >> input;
            try
            {
                list.deleteValue(input);
                cout << "Value deleted\n";
            }
            catch(Exceptions::DeletesNotExistingValue &)
            {
                cout << "Error: This value is not in this list";
            }
            break;
        default:
            break;
        }
        cout << "\nWrite command: ";
        cin >> command;
    }
    return 0;
}

