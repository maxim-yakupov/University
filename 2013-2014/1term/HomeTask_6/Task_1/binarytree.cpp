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

TreeNode* createNode(int value)
{
    return new TreeNode {value, nullptr, nullptr, nullptr};
}

bool deleteRoot(Tree& tree, TreeNode* destination)//for removeValue()
{
    TreeNode* tmp = destination;
    if (isLeaf(destination))//!!if it is tree of one element
    {
        destination = nullptr;
    }
    else if (destination->left == nullptr)//!!if root have not left branch
    {
        destination = destination->right;
    }
    else if (destination->right == nullptr)//!!if root have not right branch
    {
        destination = destination->left;
    }
    else//!!both of childs exists
    {
        TreeNode* leftSubtree = destination->left;
        destination = destination->right;
        TreeNode* parentOfLeftSubtree = destination;
        while (parentOfLeftSubtree->left != nullptr)
        {
            parentOfLeftSubtree = parentOfLeftSubtree->left;
        }
        parentOfLeftSubtree->left = leftSubtree;
        leftSubtree->parent = parentOfLeftSubtree;
    }
    tree.root = destination;
    if (tree.root != nullptr)//!!if tree is not empty
    {
        tree.root->parent = nullptr;
    }
    delete tmp;
    return true;
}

void deleteNodeFromLeftBranch(TreeNode*& destination)//for removeValue()
{
    TreeNode* leaf = destination;// semantic leaf, don't try to understand directly
    if (leaf->left == nullptr)//if left branch of deleting node is empty
    {
        destination->parent->left = leaf->right;
        if (leaf->right != nullptr)
        {
            destination->parent->left->parent = destination->parent;
        }
    }
    else
    {
        leaf = leaf->left;
        while (leaf->right != nullptr)
        {
            leaf = leaf->right;
        }
        leaf->right = destination->right;
        if (leaf->right != nullptr)
        {
            leaf->right->parent = leaf;
        }
        destination->parent->left = leaf;
        leaf->parent = destination->parent;
    }
}

void deleteNodeFromRightBranch(TreeNode*& destination)//for removeValue()
{
    TreeNode* leaf = destination;// semantic leaf, don't try to understand directly
    if (leaf->right == nullptr)
    {
        destination->parent->right = leaf->left;
        if (leaf->left != nullptr)
        {
            destination->parent->right->parent = destination->parent;
        }
    }
    else
    {
        leaf = leaf->right;
        while (leaf->left != nullptr)
        {
            leaf = leaf->left;
        }
        leaf->left = destination->left;
        if (leaf->left != nullptr)
        {
            leaf->left->parent = leaf;
        }
        destination->parent->right = leaf;
        leaf->parent = destination->parent;
    }
}

namespace BinaryTreeAPI
{
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

    bool addValue(TreeNode*& currentNode, int value)
    {
        if (currentNode == nullptr)
        {
            currentNode = createNode(value);
            return true;
        }
        else if ((currentNode->left == nullptr) && (currentNode->value > value))
        {
            currentNode->left = createNode(value);
            currentNode->left->parent = currentNode;
            return true;
        }
        else if ((currentNode->right == nullptr) && (currentNode->value < value))
        {
            currentNode->right = createNode(value);
            currentNode->right->parent = currentNode;
            return true;
        }

        if ((currentNode->left != nullptr) && (currentNode->value > value))
        {
            addValue(currentNode->left, value);
            return true;
        }
        else if ((currentNode->right != nullptr) && (currentNode->value < value))
        {
            addValue(currentNode->right, value);
            return true;
        }
        return false;
    }

    bool removeValue(Tree &tree, int value)//!!
    {
        TreeNode* destination = getByValue(tree,value);
        if (destination == nullptr)//there is not element with this value
        {
            return false;
        }
        if (destination->parent == nullptr)//if we should remove root
        {
            return deleteRoot(tree, destination);
        }
        if (destination->value < destination->parent->value)//if our node in left branch
        {
            deleteNodeFromLeftBranch(destination);
        }
        else if (destination->value > destination->parent->value)//if our node in right branch
        {
            deleteNodeFromRightBranch(destination);
        }
        delete destination;
        return true;
    }

    bool exists(Tree &tree, int value)
    {
        return getByValue(tree, value);
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

    void printAscending(TreeNode* node)//uses iostream
    {
        if (node != nullptr)
        {
            printAscending(node->left);
            printAscending(node->right);
            std::cout << node->value << " ";
        }
    }

    void printDescending(TreeNode* node)//uses iostream
    {
        if (node != nullptr)
        {
            std::cout << node->value << " ";
            printDescending(node->left);
            printDescending(node->right);
        }
    }

    void printForDebug(TreeNode* node)//uses iostream
    {
        using std::cout;
        if (node == nullptr)
        {
            cout << "null";
        }
        else
        {
            cout << "(" << node->value << " ";
            printForDebug(node->left);
            cout << " ";
            printForDebug(node->right);
            cout << ")";
        }
    }
}
