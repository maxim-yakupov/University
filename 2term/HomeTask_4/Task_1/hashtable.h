#pragma once
#include "uniquelist.h"

class HashTable
{
public:
    HashTable(int lengthOfTable);
    ~HashTable();
    /**
     * @brief add Adds string to hash-table
     * @detailed If counter >= 1 only increases counter for 1 point
     * @param str Adding string
     */
    void add(char* str);
    /**
     * @brief remove Removes string from hash-table
     * @detailed If counter >= 1 only decreases counter for 1 point
     * @param str Removing string
     */
    void remove(char* str);
    /**
     * @brief operator () Changes hash-function & rebuild hash-table with new function
     */
    void operator()(int (*inputFunc)(char*));
    /**
     * @brief operator [] Returns pointer to C-string with searching value if it contains in hash-table
     * @param str Searching string
     * @return nullptr if not in hash-table or pointer to C-string
     */
    char* operator[](char* str);
    /**
     * @brief hash Executes current hash-function with 'str' string as parameter
     * @param str String, which hash calculates
     * @return Current hash of 'str'
     */
    unsigned int hash(char* str);
    /**
     * @brief print Prints hash-table
     */
    void print();
    /**
     * @brief size Returns size of hash-table
     * @return Size of hash-table
     */
    unsigned int size();
    /**
     * @brief numberOfUniqueElements Number of unique elements in hash-table
     * @return Number of unique elements in hash-table
     */
    unsigned int numberOfUniqueElements();
    /**
     * @brief loadFactor Calculates load-factor of hash-table
     * @return Load-factor
     */
    double loadFactor();
    /**
     * @brief numberOfConflicts Returns number of conflict cells
     * @return Number of conflict cells
     */
    unsigned int numberOfConflicts();
    /**
     * @brief biggestLengthOfConflict Returns length of the biggest chain
     * @return Length of the biggest chain
     */
    unsigned int biggestLengthOfConflict();
private:
    UniqueList** table;
    unsigned int tableSize;
    int (*hashFunc)(char*);
};
