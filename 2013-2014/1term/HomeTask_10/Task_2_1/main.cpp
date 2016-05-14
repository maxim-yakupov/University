#include <iostream>
#include <fstream>
#include "mathtree.h"

using namespace std;
using namespace MathTreeAPI;

bool getInFileInformation(ifstream &infile);
bool openOutFile(fstream &outfile);
void readTree(ifstream& infile, MathNode*& node);
bool isLeaf(MathNode* node);

int main()
{
    //!!____SETTING_STREAM____
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    fstream out;
    cout << (openOutFile(out) ? "Result in file 'decompressed_output.txt'" : "Was created file 'decompressed_output.txt'");
    //!!_______________________
    //!!_____READING_TREE______
    MathTree myTree = create();
    readTree(infile, myTree.root);
//    printForDebug(myTree.root);
    //!!_______________________
    //!!___DECOMPRESSING_______
    cout << endl;
    char ch = '\0';
    infile.get();
    MathNode* current = myTree.root;
    while (!infile.eof())
    {
        ch = infile.get();
        if (isLeaf(current))
        {
            cout << current->operation;
            out << current->operation;
            current = myTree.root;
        }
        if (ch == '0')
        {
            current = current->left;
        }
        else if (ch == '1')
        {
            current = current->right;
        }
    }
    //!!_______________________
    //!!__CLEANING_MEMORY______
    cleanUp(myTree);
    //!!_______________________
    //!!____CLOSING_STREAM____
    infile.close();
    out.close();
    //!!______________________
    return 0;
}

bool isLeaf(MathNode* node)
{
    if (node->left)
        if (node->right)
            return 0;
    return 1;
}

void readTree(ifstream& infile, MathNode*& node)
{
    char ch = infile.get();
    int t = 0;
    if (ch == '\3')
    {
        infile >> t;
        infile.get();
        ch = infile.get();
        add(node, t, ch);
        readTree(infile, node->left);
        if (node->left) node->left->parent = node;
        readTree(infile, node->right);
        if (node->right) node->right->parent = node;
        infile.get();
    }
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
    outfile.open("decompressed_output.txt");
    if (!outfile.is_open())//if don't exists
    {
        outfile.open("decompressed_output.txt", ios_base::in | ios_base::out | ios_base::trunc);//create
        return false;
    }
    else
    {
        return true;
    }
}
