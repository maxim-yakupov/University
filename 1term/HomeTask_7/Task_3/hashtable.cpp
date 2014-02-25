#include "hashtable.h"

unsigned int abs(int input);
int hashF(const char* str);

namespace hashTableAPI
{
    void initHashTable(Chain* hashTable[], int lengthOfTable)
    {
        for (int i = 0; i < lengthOfTable; i++)
        {
            hashTable[i] = new Chain {nullptr, stringAPI::createString(""), 0};
        }
    }

    unsigned int hash(const char* str, unsigned int size)
    {
        return abs(hashF(str)) % size;
    }

    Chain* searchInHashTable(Chain* hashTable[], stringAPI::String input, unsigned int tableSize)
    {
        Chain* c = hashTable[abs(hashF(input.beginning)) % tableSize];
        while ((c != nullptr) && !stringAPI::areEqualStrings(c->svalue, input))
        {
            c = c->next;
        }
        return c;
    }

    bool deleteFromHashTable(Chain* hashTable[], stringAPI::String input, unsigned int tableSize, unsigned int& amountOfWords, unsigned int& busyCells)
    {
        Chain* c = hashTable[abs(hashF(input.beginning)) % tableSize];
        Chain* prev = nullptr;
        while ((c != nullptr) && (!stringAPI::areEqualStrings(c->svalue, input)))
        {
            prev = c;
            c = c->next;
        }
        if (c != nullptr)
        {
            if (prev)
            {
                prev->next = c->next;
            }
            else if (c->next)
            {
                hashTable[abs(hashF(input.beginning)) % tableSize] = c->next;
            }
            else
            {
                hashTable[abs(hashF(input.beginning)) % tableSize] =  new Chain {nullptr, stringAPI::createString(""), 0};
                busyCells--;
            }
            amountOfWords--;
            stringAPI::deleteString(c->svalue);
            delete c;
        }
        return c;
    }

    void addToHashTable(Chain* hashTable[], stringAPI::String input, unsigned int& busyCells, unsigned int& amountOfWords, unsigned int tableSize)
    {
        int hash = abs(hashF(input.beginning)) % tableSize;
        if (hashTable[hash]->svalue.beginning[0] == '\0')
        {
            hashTable[hash]->svalue = stringAPI::clone(input);
            hashTable[hash]->counter = 1;
            busyCells++;//!!
            amountOfWords++;//!!
        }
        else
        {
            Chain* current = hashTable[hash];
            while ((!stringAPI::areEqualStrings(current->svalue, input)) && (nullptr != current->next)) current = current->next;

            if (stringAPI::areEqualStrings(current->svalue, input))
            {
                current->counter++;
            }
            else
            {
                current->next = new Chain {nullptr, stringAPI::createString(), 0};
                current = current->next;
                current->svalue = stringAPI::clone(input);
                current->counter = 1;
                amountOfWords++;//!!
            }
        }
    }
}

unsigned int abs(int input)
{
    if (input < 0)
    {
        return -input;
    }
    else
    {
        return input;
    }
}

int hashF(const char* str)
{
    if (str[0] == '\0')
    {
    return 613;
    }
    else
    {
        return (str[0] + hashF(&str[1])) * str[0];
    }
}
