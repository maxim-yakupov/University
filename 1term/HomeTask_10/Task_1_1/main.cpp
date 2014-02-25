#include <iostream>
#include <fstream>
#include "binarytree.h"
#include "lists_mod.h"
#include "maxstring.h"

using namespace std;
using namespace BinaryTreeAPI;
using namespace lists;
using namespace stringAPI;

void printTree(TreeNode* node, fstream &out);
bool getInFileInformation(ifstream &infile);
bool openOutFile(fstream &outfile);
void swapElementsInList(int first, int second, List* list);
void quickSort(List* list, int leftLimiter, int rightLimiter);
void makeHuffmanTable(String table[], TreeNode* node, String str);

int main()
{
    //!!____SETTING_STREAM____
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    fstream out;
    cout << (openOutFile(out) ? "Result in file 'compressed_output.txt'" : "Was created file 'compressed_output.txt'");
    //!!_______________________
    Tree myTree = create();
    String str = createString();
    //!!____COUNT_FREQUENCY____
    int frequency[256];
    for (int i = 0; i < 256; i++)
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
    //!!_________________________
    //
    //!!____MAKING_LIST__________
    List* queue = initList(createNode(0, 0));
    int alphabetPower = 0;
    for (int i = 0; i< 256; i++)
    {
        if (frequency[i])
        {
            cout << endl;
            cout << (char) i << " " << (int) frequency[i];
            alphabetPower++;
            addElement(getElement(queue->length, queue), createNode(frequency[i], (char) i), queue);
        }
    }
    //!!___________________________
    //!!_____MAKING_TREE___________
    quickSort(queue, 1, queue->length);

    while (queue->length > 1)
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
    //
    myTree.root = getElement(1, queue)->node;
    //!!______________________________
    //!!_____MAKING_HUFFMAN_TABLE_____
    String table[256] = {nullptr, 0};
    makeHuffmanTable(table, myTree.root, {nullptr, 0});
    //test
    for (int i = 0; i < 256; i++)
    {
        if(table[i].length)
        {
            cout << "\n'" << (char) i << "' '" << stringToCharPtr(table[i]) << "'";
        }
    }
    //end_test
    //!!______________________________
    //!!____PRINTING_OF_STRUCTURES____
    cout << endl;
    printTree(myTree.root, out);//print Huffman tree
    out << endl;
    cout << "\n" << stringToCharPtr(str);
    cout << endl;
    for (int i = 0; i < str.length; i++)
    {
        cout << stringToCharPtr(table[(int) str.beginning[i]]);
        out << stringToCharPtr(table[(int) str.beginning[i]]);//result
    }
    //!!_______________________________
    //!!___CLEAN_MEMORY______
    for (int i = 0; i < 256; i++)
    {
        deleteString(table[i]);
    }
    deleteString(str);
    deleteList(queue);
    cleanUp(myTree);
    //!!______________________
    //!!____CLOSING_STREAM____
    infile.close();
    out.close();
    //!!______________________
    return 0;
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
            String strLeft = createString();
            strLeft = clone(str);
            concat(strLeft, {"0", 1});
            makeHuffmanTable(table, node->left, strLeft);
            deleteString(strLeft);
        }
        if (node->right)
        {
            String strRight = createString();
            strRight = clone(str);
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
/*
void quickSort(List* list, int leftLimiter, int rightLimiter)//float sort (i don't want to change name in main() )
{
    for (int i = leftLimiter; i < rightLimiter; i++)
    {
        for (int j = i + 1; j <= rightLimiter; j++)
        {
            if (getElement(i, list)->node->value > getElement(j, list)->node->value)
            {
                swapElementsInList(i, j, list);
            };
        }
    }
}
*/
///*
void quickSort(List* list, int leftLimiter, int rightLimiter)
{
    if (leftLimiter == rightLimiter - 1)
    {
        if (getElement(leftLimiter, list)->node->value > getElement(rightLimiter, list)->node->value)
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
            if (left < right)
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
//*/
void printTree(TreeNode* node, fstream& out)
{
//    using std::cout;
    if (nullptr == node)
    {
//        cout << "null";
        out << '\2';//service symbol
    }
    else
    {
//        cout << "([" << node->value << "|'" << node->letter << "'] ";
        out << "\3" << node->value << "\5" << node->letter;//(
//        out << " ";
        printTree(node->left, out);
//        cout << " ";
//        out << " ";
        printTree(node->right, out);
//        cout << ")";
        out << "\4";//)
    }
}
