#pragma once
#include <iostream>
#include <fstream>

namespace PhoneBookAPI
{
    struct Phone
    {
        char* name;
        char* phone;
        Phone* next;
    };

    struct PhoneBook
    {
        Phone* head;
    };

    PhoneBook* create();
    bool openPhoneBase(std::fstream &phoneBase);
    void addRecord(char name[], char phone[], PhoneBook *phonebook);
    char* getPhoneByName(char name[50], PhoneBook *phonebook);
    char* getNameByPhone(char phone[12], PhoneBook *phonebook);
    void readPhonebookFromBase(std::fstream &phoneBase, PhoneBook* phonebook);
    void savePhonebookToBase(std::fstream &phoneBase, PhoneBook* phonebook);
    void wipePhonebook(PhoneBook* phonebook);
}
