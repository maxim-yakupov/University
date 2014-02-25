#include <iostream>
#include "mathtree.h"

using MathTreeAPI::MathNode;
using MathTreeAPI::MathTree;

MathNode* createNode(double value, char operation)//for create
{
    return new MathNode {value, operation, nullptr, nullptr, nullptr};
}

void cleanSubMathTree(MathNode*& node)//for cleanUp
{
    if (node->left != nullptr)
    {
        cleanSubMathTree(node->left);
    }
    if (node->right != nullptr)
    {
        cleanSubMathTree(node->right);
    }
    node->parent = nullptr;
    delete node;
}

namespace MathTreeAPI
{
    MathTree create()
    {
        MathTree tree;
        tree.root = nullptr;
        return tree;
    }

    void add(MathNode*& node, double value, char operation)
    {
        node = createNode(value, operation);
    }

    void cleanUp(MathTree& tree)
    {
        MathNode*& root = tree.root;
        if (root != nullptr)
        {
            cleanSubMathTree(root);
            root = nullptr;
        }
    }

    void printForDebug(MathNode* node)//uses iostream
    {
        using std::cout;
        if (node == nullptr)
        {
            cout << "null";
        }
//        else if (node->operation == 'n')
//        {
//            cout << node->value;
//        }
        else
        {
            cout << "(" << node->operation << " ";
            printForDebug(node->left);
            cout << " ";
            printForDebug(node->right);
            cout << ")";
        }
    }
}
