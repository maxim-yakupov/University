#include <iostream>
#include <fstream>
#include "maxstring.h"
#include "hashtable.h"

using namespace std;
using namespace stringAPI;
using namespace hashTableAPI;

bool isSeparator(char input);

bool getInFileInformation(ifstream &infile);

void printHashTable(Chain *hashTable[], unsigned int tableSize);
void printHashTableStats(unsigned int amountOfWords, unsigned int tableSize, unsigned int busyCells, unsigned int maxLengthOfChain);

int main()
{
    //!!__HASHTABLE_VARIABLES__
    const int tableSize = 2;

    unsigned int busyCells = 0;
    unsigned int maxLengthOfChain = 0;
    unsigned int amountOfWords = 0;
    Chain* hashTable[tableSize];
    initHashTable(hashTable, tableSize);
    //!!_______________________

    //!!____SETTING_STREAM_____
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    //!!_______________________
    //!!_____READING_WORDS_____
    String input = createString("");
    int i = 0;
    char ch = infile.get();
    concat(input, {&ch, 1});
    while (!infile.eof())
    {
        if (isSeparator(input.beginning[i]) || infile.eof())
        {
            String copyStr = subString(input, 0, length(input) - 1);
            changeString(input, stringToCharPtr(copyStr));
            deleteString(copyStr);
            if (input.beginning[0])
            {
                addToHashTable(hashTable, input, busyCells, amountOfWords, tableSize);
            }
            i = -1;
            changeString(input, "");
        }
        i++;
        ch = infile.get();
        concat(input, {&ch, 1});
    }
    changeString(input, stringToCharPtr(subString(input, 0, length(input) - 1)));
    if (input.beginning[0])
    {
        addToHashTable(hashTable, input, busyCells, amountOfWords, tableSize);
    }
    //!!_______________________
    //!!____CLOSING_STREAM_____
    infile.close();
    //!!_______________________

    //!!___MAKING_ORDERS_______
    while (true)
    {
        cout << "\n ------\n|enter \n|b-to exit, \n|s-to search, \n|d-to delete, \n|a-to add, \n|p-to print, \n|c-to clear screen: ";
        changeString(input, "");
        while ('\n' != (ch = cin.get())) concat(input, {&ch, 1});
        if (areEqualStrings(input, {"b", 1}))
        {
            break;
        }
        else if(areEqualStrings(input, {"s", 1}))
        {
            cout << "write value: ";
            changeString(input, "");
            while ('\n' != (ch = cin.get())) concat(input, {&ch, 1});
            Chain* current = searchInHashTable(hashTable, input, tableSize);
            cout << "\nvalue: '"
                 << (current ? stringToCharPtr(current->svalue) : "")
                 << "' counter: "
                 << (current ? current->counter : -1)
                 << " hash: "
                 << hashTableAPI::hash(input.beginning, tableSize);
        }
        else if(areEqualStrings(input, {"d", 1}))
        {
            cout << "write value: ";
            changeString(input, "");
            while ('\n' != (ch = cin.get())) concat(input, {&ch, 1});
            if (deleteFromHashTable(hashTable, input, tableSize, amountOfWords, busyCells))
            {
                cout << "success";
            }
            else
            {
                cout << "fail";
            }
        }
        else if(areEqualStrings(input, {"a", 1}))
        {
            cout << "write value: ";
            changeString(input, "");
            while ('\n' != (ch = cin.get())) concat(input, {&ch, 1});
            addToHashTable(hashTable, input, busyCells, amountOfWords, tableSize);
        }
        else if(areEqualStrings(input, {"p", 1}))
        {
            printHashTable(hashTable, tableSize);
            //!!____COUNTING_STATS_____
            for (int i = 0; i < tableSize; i++)
            {
                Chain* c = hashTable[i];
                unsigned int currentLengthOfChain = 0;
                while (c != nullptr)
                {
                    if (c->svalue.beginning[0]) currentLengthOfChain++;//!!
                    c = c->next;
                }
                if (currentLengthOfChain > maxLengthOfChain) maxLengthOfChain = currentLengthOfChain;
            }
            //!!_______________________
            printHashTableStats(amountOfWords, tableSize, busyCells, maxLengthOfChain);
        }
        else if(areEqualStrings(input, {"c", 1}))
        {
            system("cls");
        }
    }
    //!!_______________________
    deleteString(input);
    //!!_CLEARING_OF_HASHTABLE_
    for (int i = 0; i < tableSize; i++)
    {
        do
        {
            Chain*& c = hashTable[i];
            Chain* next = c->next;
            deleteString(c->svalue);
            delete c;
            c = next;
        }while (hashTable[i] != nullptr);
    }
    //!!_______________________
    return 0;
}


bool isSeparator(char input)
{
    return !(((input >= 'a') && (input <= 'z')) || ((input >= 'A') && (input <= 'Z')));
}

bool getInFileInformation(ifstream &infile)
{
    cout << "Write file name(for input)[only utf-8 chars!]: ";
    char destination[100] = {'\0'};
    cin.getline(destination, 100);
    cout << "Trying to read file '" << destination << "' . . ." << endl;
    infile.open(destination);
    if (!infile.is_open())
    {
        cout << "Ups, i can't read your file! (maybe it is in wrong place)" << endl;
        return 1;
    }
    else
    {
        cout << "File successfuly loaded" << endl;
    }
    cout << endl;
    return 0;
}

//
void printHashTable(Chain* hashTable[], unsigned int tableSize)
{
    std::cout << "\n====printing====" << std::endl;
    for (unsigned int i = 0; i < tableSize; i++)
    {
        Chain* c = hashTable[i];
        while (c != nullptr)
        {
            std::cout << "hash " << i << ": '" << stringAPI::stringToCharPtr(c->svalue) << "' counter:" << c->counter << std::endl;
            c = c->next;
            if (c == nullptr)
            {
                std::cout << "\n================" << std::endl;
            }
        }
    }
}

void printHashTableStats(unsigned int amountOfWords, unsigned int tableSize, unsigned int busyCells, unsigned int maxLengthOfChain)
{
    using std::cout;
    cout << "\nload factor: " << ((float)amountOfWords / tableSize);
    cout << "\namount of words: " << amountOfWords;
    cout << "\nempty cells: " << tableSize - busyCells;
    cout << "\naverage length of chains: " << (amountOfWords ? ((float)amountOfWords / busyCells) : 0);
    cout << "\nmax length of chain: " << maxLengthOfChain;
}
