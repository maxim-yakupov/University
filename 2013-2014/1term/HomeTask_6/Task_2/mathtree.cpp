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

    double calculateExpression(MathNode*& node)
    {
        if (node->operation == '+')
        {
            return calculateExpression(node->left) + calculateExpression(node->right);
        }
        else if (node->operation == '-')
        {
            return calculateExpression(node->left) - calculateExpression(node->right);
        }
        else if (node->operation == '*')
        {
            return calculateExpression(node->left) * calculateExpression(node->right);
        }
        else if (node->operation == '/')
        {
            return calculateExpression(node->left) / calculateExpression(node->right);
        }
        else
        {
            return node->value;
        }
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

    void printExpression(MathNode* node, int fl)//uses iostream
    {
        if (node != nullptr)
        {
            printExpression(node->left, -1);

            if (node->operation == 'n')
            {
                if (fl == -1) std::cout << "(";
                std::cout << node->value;
                if (fl == 1) std::cout << ")";
                std::cout << " ";
            }
            else
            {
                std::cout << node->operation << " ";
            }
            printExpression(node->right, 1);
        }
    }

    void printForDebug(MathNode* node)//uses iostream
    {
        using std::cout;
        if (node == nullptr)
        {
            cout << "null";
        }
        else if (node->operation == 'n')
        {
            cout << node->value;
        }
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
