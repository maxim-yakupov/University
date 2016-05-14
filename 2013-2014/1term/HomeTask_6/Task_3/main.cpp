#include <iostream>
#include "avlbinarytree.h"

using namespace std;
using namespace BinaryTreeAPI;

void test(void);

int main()
{
//    test();
    Tree myTree = create();
    TreeNode*& root = myTree.root;
    char ch = 1;
    int t = 0;
    while (true)
    {
        cout << endl;
        cout << endl;
        cout << " ------------------------------------- " << endl;
        cout << "|enter:                               |" << endl;
        cout << " ------------------------------------- " << endl;
        cout << "|type 'a [someNumber]' to add value   |" << endl;
        cout << "|type 'p' to print tree               |" << endl;
        cout << "|type 'c' to clean up tree            |" << endl;
        cout << "|type 'd [someNumber]' to remove value|" << endl;
        cout << "|type '[anotherChar]' to exit         |" << endl;
        cout << " ------------------------------------- " << endl;
        cout << "|>>";
        cin >> ch;
        if (ch == 'p')
        {
            system("cls");
            cout << "|Debug view: ";
            printForDebug(root);
            cout << endl;
            cout << "|Ascending view: ";
            printAscending(root);
            cout << endl;
            cout << "|Descending view: ";
            printDescending(root);
        }
        else if (ch == 'c')
        {
            cleanUp(myTree);
            system("cls");
        }
        else if (ch == 'd')
        {
            cin >> t;
            removeValue(myTree, t);
            system("cls");
        }
        else if (ch == 'a')
        {
            cin >> t;
            addValue(root, t);
        }
        else
        {
            break;
        }
    }

    cleanUp(myTree);
    return 0;
}

void test(void)
{
    cout << "TEST!!!" << endl;
    Tree myTree = create();
    TreeNode*& root = myTree.root;
    cout << "add 5:" << addValue(root, 5) << endl;
    cout << "add 2:" << addValue(root, 2) << endl;
    cout << "add 8:" << addValue(root, 8) << endl;
    cout << "exists 5:" << exists(myTree, 5) << endl;
    cout << "exists 2:" << exists(myTree, 2) << endl;
    cout << "exists 8:" << exists(myTree, 8) << endl;

    cout << "!!---exists 10:" << exists(myTree, 10) << endl;

    printForDebug(root);
    cout << endl;
    cout << "cleaning up tree...";
    cleanUp(myTree);
    cout << endl;
    cout << "now our tree is ";
    printForDebug(root);
    cout << endl;
    cout << "Press [Enter]";
    getchar();
    system("cls");
}
