#pragma once
#include "singlylinkedlist.h"

/**
 * @brief The UniqueList class
 * @detailed Class of list without equal values
 */
class UniqueList:public SinglyLinkedList
{
public:
    UniqueList();
    /**
     * @brief contains Checks if value in list
     * @param value Value, that trying to find
     * @return Returns true if value in list, returns false if not
     */
    ListElement *contains(char* value);
    /**
     * @brief addValue Adds value in list, if this value is not in the list
     * @param value Value, which trying to add
     */
    void addValue(char* value);
    /**
     * @brief deleteValue Deletes value from list, if this value is in the list
     * @param value Value, which trying to delete
     */
    void deleteValue(char* value);
    void print();
    /**
     * @brief retH Returns pointer to head element
     * @return Pointer to head element
     */
    ListElement *retH();
};
