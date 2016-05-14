#include <iostream>
#include <fstream>
#include "Phonebook.h"

using namespace std;
using namespace PhoneBookAPI;

int main()
{
    PhoneBook* phonebook = create();

    fstream phoneBase;
    if (openPhoneBase(phoneBase))
    {
        cout << "File of phonebook has been found" << endl;
    }
    else
    {
        cout << "File of phonebook was created" << endl;
    }

    readPhonebookFromBase(phoneBase, phonebook);

    char choice = '4';
    while (choice != '0')
    {
        cout << "**************************************\n";
        cout << "* 0 - exit                           *\n";
        cout << "* 1 - add a record to phonebook      *\n";
        cout << "* 2 - find phone by a name           *\n";
        cout << "* 3 - find name by a phone           *\n";
        cout << "* 4 - save phonebook                 *\n";
        cout << "**************************************\n";
        cout << "Write command:";
        cin >> choice;
        system("cls");
        switch (choice)
        {
            case '1':
            {
                cout << "Add record(length of name <= 50, length of phone number <= 12)" << endl << endl;
                char* name = new char[50] {'\0'};
                char* phone = new char[12] {'\0'};
                cout << "Write a name: ";
                cin >> name;
                cout << "Write a phone: ";
                cin >> phone;
                addRecord(name, phone, phonebook);
                break;
            };
            case '2':
            {
                cout << "Finding phone by name(length of name <= 50)" << endl << endl;
                char* name = new char[50] {'\0'};
                cout << "Write a name: ";
                cin >> name;
                cout << "Phone: " << getPhoneByName(name, phonebook) << endl;
                delete [] name;
                break;
            };
            case '3':
            {
                cout << "Finding name by phone(length of name <= 12)" << endl << endl;
                char* phone = new char[12] {'\0'};
                cout << "Write a phone: ";
                cin >> phone;
                cout << "Name: " << getNameByPhone(phone, phonebook) << endl;
                delete [] phone;
                break;
            };
            case '4':
            {
                cout << "Phonebook saved" << endl;
                savePhonebookToBase(phoneBase, phonebook);
                break;
            };
            default:
            {
                if (choice - '0')
                {
                    cout << "Unknown command, try again" << endl;
                }
                break;
            }
        }
    }

    cout << "Wiping used memory . . ." << endl;
    wipePhonebook(phonebook);
    cout << "Done!" << endl;
    phoneBase.close();
    cout << "Good Bye!" << endl;
    return 0;
}

