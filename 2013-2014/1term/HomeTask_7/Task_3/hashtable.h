#pragma once
#include "maxstring.h"

namespace hashTableAPI
{
    struct Chain
    {
        Chain* next;
        stringAPI::String svalue;
        int counter;
    };
    void initHashTable(Chain* hashTable[], int lengthOfTable);
    unsigned int hash(const char* str, unsigned int size);
    Chain* searchInHashTable(Chain* hashTable[], stringAPI::String input, unsigned int tableSize);
    bool deleteFromHashTable(Chain* hashTable[], stringAPI::String input, unsigned int tableSize, unsigned int& amountOfWords, unsigned int& busyCells);
    void addToHashTable(Chain* hashTable[], stringAPI::String input, unsigned int& busyCells, unsigned int& amountOfWords, unsigned int tableSize);
}
