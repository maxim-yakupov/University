#pragma once
#include "singlylinkedlist.h"
#include "exceptions.h"

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
    bool contains(int value);
    /**
     * @brief addValue Adds value in list, if this value is not in the list
     * @param value Value, which trying to add
     */
    void addValue(int value);
    /**
     * @brief addPos Adds value in list on it's position, if this value is not in the list
     * @param pos Position
     * @param value Value, which trying to add
     */
    void addPos(int pos, int value);
    /**
     * @brief deleteValue Deletes value from list, if this value is in the list
     * @param value Value, which trying to delete
     */
    void deleteValue(int value);
};
