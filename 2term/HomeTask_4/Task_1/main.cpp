#include <iostream>
#include "hashtable.h"
#include "testHashTable.h"

using namespace std;

class HashX : public HashFunction
{
public:
    int hash(const char *str)
    {
        int res = 0;
        for (int i = 0; str[i]; i++)
        {
            res = (res * 3 - 100 + str[i] - '0') % 5;
        };
        return res;
    }
};

class HashY : public HashFunction
{
public:
    int hash(const char *str)
    {
        int res = 0;
        for (int i = 0; str[i]; i++)
        {
            res = (res * 3 - 100 + str[i] - '0') % 3;
        };
        return res;
    }
};

class HashZ : public HashFunction
{
public:
    int hash(const char *str)
    {
        int res = 0;
        for (int i = 0; str[i]; i++)
        {
            res = (res * 7 - 666 + str[i] - '0') % 1984;
        };
        return res;
    }
};

class HashConst : public HashFunction
{
public:
    int hash(const char *str)
    {
        return 1;
    }
};

int main()
{
    //test
    TestHashTable testHashTable;
    QTest::qExec(&testHashTable);
    //end test

    unsigned int size = 1;
    cout << "Write size of hash-table: ";
    cin >> size;
    HashTable ht(size);

    HashX* hX = new HashX;
    HashY* hY = new HashY;
    HashZ* hZ = new HashZ;
    HashConst* hConst = new HashConst;

    char command = '?';
    char* input = new char[500];
    while (command != 'q')
    {
        bool exists = true;
        switch (command) {
        case '?':
            cout << "Commands list:\n";
            cout << "'?' - this help;\n";
            cout << "'h' - get hash of input string;\n";
            cout << "'a' - add value;\n";
            cout << "'d' - delete value;\n";
            cout << "'f' - check string(in table or not);\n";
            cout << "'p' - print table;\n";
            cout << "'s' - print stats;\n";
            cout << "'c' - change hash-function;\n";
            cout << "'q' - end program.\n";
            break;
        case 'h':
            cout << "string>> ";
            cin >> input;
            cout << "Hash of '" << input << "' = " << ht.hash(input) << endl;
            break;
        case 'p':
            cout << "Your hash-table:\n";
            ht.print();
            break;
        case 'a':
            cout << "add>> ";
            cin >> input;
            ht.add(input);
            cout << "Value added\n";
            break;
        case 'd':
            cout << "delete>> ";
            cin >> input;
            exists = ht[input];
            cout << (exists ? "Value deleting\n" : "Nothing to delete\n");
            ht.remove(input);
            cout << (exists ? "Deleted\n" : " ");
            break;
        case 'f':
            cout << "find>> ";
            cin >> input;
            cout << (ht[input] ? "Value in table\n" : "Value is not in table\n");
            break;
        case 's':
            cout << "Table size: " << ht.size() << endl;
            cout << "Number of unique elements in table: " << ht.numberOfUniqueElements() << endl;
            cout << "Number of conflict cells in table: " << ht.numberOfConflicts() << endl;
            cout << "Biggest length of chains: " << ht.biggestLengthOfConflict() << endl;
            cout << "Load-factor: " << ht.loadFactor() << endl;
            break;
        case 'c':
            cout << "Choose hash-function('x', 'y', 'z', '1')\n";
            cout << "change_hash>> ";
            cin >> input;
            switch (*input)
            {
            case 'x':
                ht(hX);
                break;
            case 'y':
                ht(hY);
                break;
            case 'z':
                ht(hZ);
                break;
            case '1':
                ht(hConst);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        cout << "\nWrite command: ";
        cin >> command;
    }
    delete input;
    return 0;
}

