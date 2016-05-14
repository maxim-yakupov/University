#include <iostream>
#include <fstream>
#include "binarytree.h"
#include "lists_mod.h"
#include "maxstring.h"

using namespace std;
using namespace BinaryTreeAPI;
using namespace lists;
using namespace stringAPI;

const int maxCode = 256;

bool getInFileInformation(ifstream &infile);
bool openOutFile(fstream &outfile);

bool countFrequency(ifstream& infile, int* frequency, String &str);
void makeListOfLetters(List* queue, int* frequency);
void quickSort(List* list, int leftLimiter, int rightLimiter);
void mergeFirstNodes(List* queue);
void makeHuffmanTable(String table[], TreeNode* node, String str);

void printTree(TreeNode* node, fstream &out);
void deleteHuffmanTable(String table[]);

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    fstream out;
    cout << (openOutFile(out) ? "Result in file 'compressed_output.txt'" : "Was created file 'compressed_output.txt'");

    Tree myTree = create();
    String str = createString();

    int frequency[maxCode];
    if (countFrequency(infile, frequency, str))
    {
        return 1;
    }

    List* queue = initList(createNode(0, 0));
    makeListOfLetters(queue, frequency);

    quickSort(queue, 1, queue->length);
    while (queue->length > 1)
    {
        mergeFirstNodes(queue);
    }

    myTree.root = getElement(1, queue)->node;

    String table[maxCode] = {nullptr, 0};
    makeHuffmanTable(table, myTree.root, {nullptr, 0});
    //writing_codes
    for (int i = 0; i < maxCode; i++)
    {
        if(table[i].length)
        {
            cout << "\n'" << (char) i << "' '" << stringToCharPtr(table[i]) << "'";
        }
    }
    //end_writing_codes

    printTree(myTree.root, out);//print Huffman tree
    out << endl;

    cout << "\n\n" << stringToCharPtr(str) << endl;

    for (int i = 0; i < str.length; i++)
    {
        cout << stringToCharPtr(table[(int) str.beginning[i]]);
        out << stringToCharPtr(table[(int) str.beginning[i]]);//result
    }

    deleteHuffmanTable(table);
    deleteString(str);
    deleteList(queue);
    cleanUp(myTree);
    infile.close();
    out.close();
    return 0;
}

void deleteHuffmanTable(String table[])
{
    for (int i = 0; i < maxCode; i++)
    {
        deleteString(table[i]);
    }
}

bool countFrequency(ifstream& infile, int *frequency, String& str)
{
    for (int i = 0; i < maxCode; i++)//init with 0
    {
        frequency[i] = 0;
    }

    char letter = infile.get();
    if (infile.eof())
    {
        cout << "\n\aFile is empty!";
        return 1;
    }
    else
    {
        infile.unget();
    }
    while (!infile.eof())
    {
        letter = infile.get();
        if (letter < 10)//not letter or symbol
        {
            continue;
        }
        concat(str, {&letter, 1});
        frequency[(int) letter]++;
    }
    return 0;
}

void mergeFirstNodes(List* queue)
{
    TreeNode* current = new TreeNode {0, 0, nullptr, nullptr, nullptr};
    current->left = getElement(1, queue)->node;
    current->right = getElement(2, queue)->node;
    current->value = current->left->value + current->right->value;
    current->left->parent = current;
    current->right->parent = current;
    deleteElement(getElement(0, queue), queue);
    getElement(1, queue)->node = current;
    quickSort(queue, 1, queue->length);
}

void makeListOfLetters(List* queue, int* frequency)
{
    for (int i = 0; i< maxCode; i++)
    {
        if (frequency[i])
        {
            cout << endl;
            cout << (char) i << " " << (int) frequency[i];
            addElement(getElement(queue->length, queue), createNode(frequency[i], (char) i), queue);
        }
    }
}

void makeHuffmanTable(String table[], TreeNode* node, String str)
{
    if (isLeaf(node))
    {
        String record = createString();
        record = clone(str);
        table[(int) node->letter] = record;
    }
    else
    {
        if (node->left)
        {
            String strLeft = clone(str);
            concat(strLeft, {"0", 1});
            makeHuffmanTable(table, node->left, strLeft);
            deleteString(strLeft);
        }
        if (node->right)
        {
            String strRight = clone(str);
            concat(strRight, {"1", 1});
            makeHuffmanTable(table, node->right, strRight);
            deleteString(strRight);
        }
    }
}

void swapElementsInList(int first, int second, List* list)
{
    addElement(getElement(second, list), getElement(first, list)->node, list);
    deleteElement(getElement(first - 1, list), list);
    addElement(getElement(first - 1, list), getElement(second - 1, list)->node, list);
    deleteElement(getElement(second - 1, list), list);
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

bool openOutFile(fstream &outfile)
{
    outfile.open("compressed_output.txt", ios_base::trunc);
    if (!outfile.is_open())//if don't exists
    {
        outfile.open("compressed_output.txt", ios_base::in | ios_base::out | ios_base::trunc);//create
        return false;
    }
    else
    {
        return true;
    }
}

void quickSort(List* list, int leftLimiter, int rightLimiter)
{
    if (leftLimiter == rightLimiter - 1)
    {
        if (getElement(leftLimiter, list)->node->value >= getElement(rightLimiter, list)->node->value)//=
        {
            swapElementsInList(leftLimiter, rightLimiter, list);
        };
    }
    else if (leftLimiter != rightLimiter)
    {
        const int base = getElement(list->length, list)->node->value;
        int left = leftLimiter;
        int right = rightLimiter;
        while (left <= right)
        {
            while ((left <= rightLimiter) && (getElement(left, list)->node->value <= base))
            {
                left++;
            };
            while ((right >= leftLimiter) && (getElement(right, list)->node->value > base))
            {
                right--;
            };
            if (left <= right)//=
            {
                swapElementsInList(left, right, list);
            }
            else
            {
                if (left <= rightLimiter)
                {
                    quickSort(list, left, rightLimiter);
                    quickSort(list, leftLimiter, left - 1);
                }
                else
                {
                    quickSort(list, leftLimiter, right - 1);
                    quickSort(list, right, rightLimiter);
                };
            };
        };
    };
}

void printTree(TreeNode* node, fstream& out)
{
    if (nullptr == node)
    {
        out << "n";
    }
    else
    {
        out << "(" << node->value << "" << node->letter << " ";
        printTree(node->left, out);
        out << " ";
        printTree(node->right, out);
        out << ")";
    }
}
