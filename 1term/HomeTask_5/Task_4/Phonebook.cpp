#include "Phonebook.h"

bool areEqualStrings(char* first, char* second)
{
    int counter = 0;
    bool isEqual = true;
    while (first[counter] != '\0')
    {
        if (first[counter] != second[counter])
        {
            isEqual = false;
        }
        counter++;
    }
    if (first[counter] != second[counter])
    {
        isEqual = false;
    }
    return isEqual;
}

namespace PhoneBookAPI
{
    using std::ios_base;
    using std::cout;
    using std::endl;
    using std::fstream;

    PhoneBook* create()
    {
        return new PhoneBook {nullptr};
    }

    bool openPhoneBase(fstream &phoneBase)
    {
        phoneBase.open("phonebook.txt");
        if (!phoneBase.is_open())//if don't exists
        {
            phoneBase.open("phonebook.txt", ios_base::in | ios_base::out | ios_base::trunc);//create
            return false;
        }
        else
        {
            return true;
        }
    }
    void addRecord(char name[], char phone[], PhoneBook* phonebook)
    {
        Phone* newRecord = new Phone {name, phone, phonebook->head};
        phonebook->head = newRecord;
    }

    char* getPhoneByName(char name[50], PhoneBook *phonebook)
    {
        Phone* current = phonebook->head;
        while ((current != nullptr) && (!areEqualStrings(current->name, name)))
        {
            current = current->next;
        }
        if (current != nullptr)
        {
            return current->phone;
        }
        else
        {
            return "there is not records with this name";
        }
    }

    char* getNameByPhone(char phone[12], PhoneBook *phonebook)
    {
        Phone* current = phonebook->head;
        while ((current != nullptr) && (!areEqualStrings(current->phone, phone)))
        {
            current = current->next;
        }
        if (current != nullptr)
        {
            return current->name;
        }
        else
        {
            return "there is not records with this phone number";
        }
    }

    void readPhonebookFromBase(fstream &phoneBase, PhoneBook* phonebook)
    {
        while (!phoneBase.eof())
        {
            char* name = new char[50] {'\0'};
            char* phone = new char[12] {'\0'};
            phoneBase >> name >> phone;
            if (name[0] != '\0')
            {
                addRecord(name, phone, phonebook);
            }
            else
            {
                delete [] name;
                delete [] phone;
            }
        }
    }

    void savePhonebookToBase(fstream &phoneBase, PhoneBook* phonebook)
    {
        phoneBase.close();
        int checkRemovement = remove("phonebook.txt");
        phoneBase.open("phonebook.txt", ios_base::in | ios_base::out | ios_base::trunc);
        Phone* current = phonebook->head;
        while (current != nullptr)
        {
            phoneBase << current->name << " " << current->phone << endl;
            current = current->next;
        }
    }

    void wipePhonebook(PhoneBook* phonebook)
    {
        while (phonebook->head != nullptr)
        {
            Phone* temp = phonebook->head;
            phonebook->head = temp->next;
            delete [] temp->name;
            delete [] temp->phone;
            delete temp;
        }
        delete phonebook;
    }
}
