#include <iostream>
#include <fstream>
#include "mathtree.h"

using namespace std;
using namespace MathTreeAPI;

bool getInFileInformation(ifstream &infile);
bool openOutFile(fstream &outfile);
void readTree(ifstream& infile, MathNode*& node);
bool isLeaf(MathNode* node);
void decompressing(ifstream& infile, MathTree& myTree, fstream &out);

int main()
{
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    fstream out;
    cout << (openOutFile(out) ? "Result in file 'decompressed_output.txt'" : "Was created file 'decompressed_output.txt'");

    MathTree myTree = create();
    readTree(infile, myTree.root);

    decompressing(infile, myTree, out);

    cleanUp(myTree);

    infile.close();
    out.close();

    return 0;
}

void decompressing(ifstream& infile, MathTree& myTree, fstream& out)
{
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
    if (ch == '(')
    {
        infile >> t;
        ch = infile.get();
        //digits_check
        char chCheck = infile.get();//infile.get();
        if (chCheck == 'n' && ch == ' ')
        {
            infile.unget();
            infile.unget();
            infile.unget();
            ch = infile.get();
            infile.get();
            t /= 10;
        }
        add(node, t, ch);
        //end
        readTree(infile, node->left);
        if (node->left) node->left->parent = node;
        infile.get();
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
    outfile.open("decompressed_output.txt", ios_base::trunc);
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
