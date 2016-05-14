#include <iostream>
#include "binarytree.h"

using BinaryTreeAPI::TreeNode;
using BinaryTreeAPI::Tree;

TreeNode* getByValue(Tree &tree, int value)
{
    TreeNode* currentNode = tree.root;
    while ((currentNode != nullptr) && (currentNode->value != value))
    {
        if (currentNode->value > value)
        {
            currentNode = currentNode->left;
        }
        else
        {
            currentNode = currentNode->right;
        }
    }
    return currentNode;
}

namespace BinaryTreeAPI
{
//
TreeNode* createNode(int value, char letter)
{
    return new TreeNode {value, letter, nullptr, nullptr, nullptr};
}
//
    Tree create()
    {
        Tree tree;
        tree.root = nullptr;
        return tree;
    }

    bool isLeaf(TreeNode* node)
    {
        return ((node->left == nullptr) && (node->right == nullptr));
    }

    bool addValue(TreeNode*& currentNode, int value, char letter)
    {
        if (currentNode == nullptr)
        {
            currentNode = createNode(value, letter);
            return true;
        }
        else if ((currentNode->left == nullptr) && (currentNode->value > value))
        {
            currentNode->left = createNode(value, letter);
            currentNode->left->parent = currentNode;
            return true;
        }
        else if ((currentNode->right == nullptr) && (currentNode->value < value))
        {
            currentNode->right = createNode(value, letter);
            currentNode->right->parent = currentNode;
            return true;
        }

        if ((currentNode->left != nullptr) && (currentNode->value > value))
        {
            addValue(currentNode->left, value, letter);
            return true;
        }
        else if ((currentNode->right != nullptr) && (currentNode->value < value))
        {
            addValue(currentNode->right, value, letter);
            return true;
        }
        return false;
    }

    void cleanSubtree(TreeNode*& node)
    {
        if (node->left != nullptr)
        {
            cleanSubtree(node->left);
        }
        if (node->right != nullptr)
        {
            cleanSubtree(node->right);
        }
        node->parent = nullptr;
        delete node;
    }

    void cleanUp(Tree& tree)
    {
        TreeNode*& root = tree.root;
        if (root != nullptr)
        {
            cleanSubtree(root);
            root = nullptr;
        }
    }
}
