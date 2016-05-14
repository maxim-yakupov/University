#include <iostream>
#include <fstream>
#include "mathtree.h"

using namespace std;
using namespace MathTreeAPI;

bool getInFileInformation(ifstream &infile);
void readExpression(ifstream& infile, MathNode*& node);
void test(void);

int main()
{
    test();
    ifstream infile;
    if (getInFileInformation(infile))
    {
        return 0;
    }
    MathTree myTree = create();
    MathNode*& root = myTree.root;
    readExpression(infile, root);
    cout << "Debug view:"; printForDebug(myTree.root);
    cout << endl;
    cout << "=======================" << endl;
    printExpression(myTree.root, 0);
    cout << "= ";
    cout << calculateExpression(myTree.root);
    cleanUp(myTree);
    return 0;
}

bool getInFileInformation(ifstream &infile)
{
    cout << "Write file name(for input)[only utf-8 chars!]: ";
    char destination[100] = {'\0'};
    cin >> destination;
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

void readExpression(ifstream& infile, MathNode*& node)
{
    char ch = infile.get();
    if (ch == '(')
    {
        ch = infile.get();
        add(node, 1, ch);
        infile.get();
        readExpression(infile, node->left);
        node->left->parent = node;
        infile.get();
        readExpression(infile, node->right);
        node->right->parent = node;
        infile.get();
    }
    else
    {
        infile.unget();
        double t = 0;
        infile >> t;
        add(node, t, 'n');
    }
}

void test(void)
{
    cout << "TEST!!!" << endl;
    MathTree myMathTree = create();
    MathNode*& root = myMathTree.root;
    printForDebug(root);
    cout << endl;
    cout << "cleaning up MathTree...";
    cleanUp(myMathTree);
    cout << endl;
    cout << "now our MathTree is ";
    printForDebug(root);
    cout << endl;
    cout << "Press [Enter]";
    getchar();
    system("cls");
}
