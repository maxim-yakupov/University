#include "hashtable.h"

HashTable::HashTable(int lengthOfTable):tableSize(lengthOfTable)
{
    table = new UniqueList*[tableSize];
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i] = new UniqueList;
    }
    hashFunc = new HashFunction;
}

HashTable::~HashTable()
{
    delete hashFunc;
    for (unsigned int i = 0; i < tableSize; i++)
    {
        delete table[i];
    }
    delete table;
}

void HashTable::add(const char *str)
{
    table[hash(str)]->addValue(str);
}

void HashTable::remove(char *str)
{
    table[hash(str)]->deleteValue(str);
}

void HashTable::operator()(HashFunction* inputFunc)
{
    delete hashFunc;
    hashFunc = inputFunc;
    UniqueList** newTable = new UniqueList*[tableSize];
    for (unsigned int i = 0; i < tableSize; i++)
    {
        newTable[i] = new UniqueList;
    }
    for (unsigned int i = 0; i < tableSize; i++)
    {
        while (table[i]->length())
        {
            char* str = table[i]->retH()->elemValue;
            newTable[hash(str)]->addValue(str);
            table[i]->deleteValue(str);
        }
    }
    for (unsigned int i = 0; i < tableSize; i++)
    {
        delete table[i];
    }
    delete table;
    table = newTable;
    newTable = nullptr;
}

const char *HashTable::operator[](char *str)//TODO: переделать под возвращение указателя UPD: или нет...
{
    char* value = nullptr;
    if (table[hash(str)]->contains(str) && table[hash(str)]->contains(str)->counter)
    {
        value = table[hash(str)]->contains(str)->elemValue;
    }
    return value;
}

unsigned int abs(int a)
{
    return ((a < 0) ? -a : a);
}

unsigned int HashTable::hash(const char *str)
{
    return abs(hashFunc->hash(str)) % tableSize;
}

void HashTable::print()
{
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i]->print();
    }
}

unsigned int HashTable::size()
{
    return tableSize;
}

unsigned int HashTable::numberOfUniqueElements()
{
    double total = 0;
    for (unsigned int i = 0; i < tableSize; i++)
    {
        total += table[i]->length();
    }
    return total;
}

double HashTable::loadFactor()
{
    return static_cast<double>(numberOfUniqueElements()) / tableSize;
}

unsigned int HashTable::numberOfConflicts()
{
    unsigned int conflicts = 0;
    for (unsigned int i = 0; i < tableSize; i++)
    {
        if (table[i]->length() > 1)
        {
            conflicts++;
        }
    }
    return conflicts;
}

unsigned int HashTable::biggestLengthOfConflict()
{
    unsigned int biggestLength = table[0]->length();
    for (unsigned int i = 1; i < tableSize; i++)
    {
        unsigned int curLength = table[i]->length();
        if (curLength > biggestLength)
        {
            biggestLength = curLength;
        }
    }
    return biggestLength;
}
