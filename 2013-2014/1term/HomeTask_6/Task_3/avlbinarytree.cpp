//notation Yoda's using
#include <iostream>
#include "avlbinarytree.h"

using BinaryTreeAPI::TreeNode;
using BinaryTreeAPI::Tree;

TreeNode* getByValue(Tree &tree, int value)
{
    TreeNode* currentNode = tree.root;
    while ((nullptr != currentNode) && (currentNode->value != value))
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

TreeNode* getParentByValue(Tree &tree, int value)
{
    TreeNode* currentNode = tree.root;
    if (value == tree.root->value)
    {
        return nullptr;
    }
    while ((nullptr != currentNode) && (nullptr != currentNode->left) && (value != currentNode->left->value)
           && (nullptr != currentNode->right) && (value != currentNode->right->value))
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
    return new TreeNode {value, 1, nullptr, nullptr};
}

//
int height(TreeNode *node)
{
    return (node ? node->height : 0);
}

int balanceFactor(TreeNode *node)
{
    return (height(node->right) - height(node->left));
}

void updateHeight(TreeNode *node)
{
   int heightLeft = height(node->left);
   int heightRight = height(node->right);
   node->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
}

TreeNode* rotateRight(TreeNode* root)
{
   TreeNode* node = root->left;
   root->left = node->right;
   node->right = root;
   updateHeight(root);
   updateHeight(node);
   return node;
}

TreeNode* rotateLeft(TreeNode* root)
{
   TreeNode* node = root->right;
   root->right = node->left;
   node->left = root;
   updateHeight(root);
   updateHeight(node);
   return node;
}

TreeNode* balance(TreeNode* p)
{
    if (nullptr == p)
    {
        return nullptr;
    }

    updateHeight(p);

    if (balanceFactor(p) == 2)
    {
        if (balanceFactor(p->right) < 0)
            p->right = rotateRight(p->right);

        return rotateLeft(p);
    }

    if (balanceFactor(p) == -2)
    {
        if (balanceFactor(p->left) > 0)
            p->left = rotateLeft(p->left);

        return rotateRight(p);
    }

    return p;
}
//

bool deleteRoot(Tree& tree, TreeNode* destination)//for removeValue()
{
    TreeNode* tmp = destination;
    if (isLeaf(destination))//!!if it is tree of one element
    {
        destination = nullptr;
    }
    else if (nullptr == destination->left)//!!if root have not left branch
    {
        destination = destination->right;
    }
    else if (nullptr == destination->right)//!!if root have not right branch
    {
        destination = destination->left;
    }
    else//!!both of childs exists
    {
        destination = balance(destination);
        TreeNode* leftSubtree = destination->left;
        destination = destination->right;
        TreeNode* parentOfLeftSubtree = destination;
        while (nullptr != parentOfLeftSubtree->left)
        {
            parentOfLeftSubtree = parentOfLeftSubtree->left;
        }
        parentOfLeftSubtree->left = leftSubtree;
    }
    tree.root = balance(destination);
    delete tmp;
    return true;
}

void rebalanceFromDeepLeft(TreeNode* parent, TreeNode* gp)
{
    if (parent->left)
    {
        rebalanceFromDeepLeft(parent->left, parent);
        gp->left = balance(parent);
    }
}

void rebalanceFromDeepRight(TreeNode* parent, TreeNode* gp)
{
    if (parent->right)
    {
        rebalanceFromDeepRight(parent->right, parent);
        gp->right = balance(parent);
    }
}

void deleteNodeFromLeftBranch(TreeNode* destination, TreeNode* parent)//for removeValue()
{
    if (nullptr == destination->left)//if left branch of deleting node is empty
    {
        parent->left = destination->right;
    }
    else
    {
        TreeNode* tmpLeftBranch = destination->left;
        parent->left = destination->right;
        destination = destination->right;
        while ((destination) && (nullptr != destination->left))
        {
            destination = destination->left;
        }
        if (destination)
        {
            destination->left = tmpLeftBranch;
        }
        else
        {
            parent->left = tmpLeftBranch;
        }
        rebalanceFromDeepLeft(parent->left, parent);
    }
}

void deleteNodeFromRightBranch(TreeNode* destination, TreeNode* parent)//for removeValue()
{
    if (nullptr == destination->right)//if left branch of deleting node is empty
    {
        parent->right = destination->left;
    }
    else
    {
        TreeNode* tmpRightBranch = destination->right;
        parent->right = destination->left;
        destination = destination->left;
        while ((destination) && (nullptr != destination->right))
        {
            destination = destination->right;
        }
        if (destination)
        {
            destination->right = tmpRightBranch;
        }
        else
        {
            parent->right = tmpRightBranch;
        }
        rebalanceFromDeepRight(parent->right, parent);
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
        return ((nullptr == node->left) && (nullptr == node->right));
    }

    //!! should make refactoring
    bool addValue(TreeNode*& currentNode, int value)
    {
        if (nullptr == currentNode)
        {
            currentNode = createNode(value);
            return true;
        }
        else if ((nullptr == currentNode->left) && (currentNode->value > value))
        {
            currentNode->left = createNode(value);
            updateHeight(currentNode);
            return true;
        }
        else if ((nullptr == currentNode->right) && (currentNode->value < value))
        {
            currentNode->right = createNode(value);
            updateHeight(currentNode);
            return true;
        }

        if ((nullptr != currentNode->left) && (currentNode->value > value))
        {
            addValue(currentNode->left, value);
            currentNode = balance(currentNode);
            return true;
        }
        else if ((nullptr != currentNode->right) && (currentNode->value < value))
        {
            addValue(currentNode->right, value);
            currentNode = balance(currentNode);
            return true;
        }
        return false;
    }

    //!! should make refactoring
    bool removeValue(Tree &tree, int value)//!!with balancing
    {
        TreeNode* destination = getByValue(tree,value);
        if (nullptr == destination)//there is not element with this value
        {
            return false;
        }
        if (destination->height == tree.root->height)//if we should remove root
        {
            return deleteRoot(tree, destination);
        }
        TreeNode* parent = getParentByValue(tree, destination->value);
        TreeNode* grandParent = getParentByValue(tree, parent->value);
        //
        if (destination->value < parent->value)//if our node in left branch
        {
            deleteNodeFromLeftBranch(destination, parent);
            parent->left = balance(parent->left);
        }
        else if (destination->value > parent->value)//if our node in right branch
        {
            deleteNodeFromRightBranch(destination, parent);
            parent->right = balance(parent->right);
        }

        if (grandParent)
        {
            if (destination->value < grandParent->value)
            {
                grandParent->left = balance(parent);
            }
            else
            {
                grandParent->right = balance(parent);
            }
        }
        else
        {
            if (destination->value < tree.root->value)
            {
                tree.root->left = balance(parent->left);
            }
            else
            {
                tree.root->right = balance(parent->right);
            }
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
        if (nullptr != node->left)
        {
            cleanSubtree(node->left);
        }
        if (nullptr != node->right)
        {
            cleanSubtree(node->right);
        }
        delete node;
    }

    void cleanUp(Tree& tree)
    {
        TreeNode*& root = tree.root;
        if (nullptr != root)
        {
            cleanSubtree(root);
            root = nullptr;
        }
    }

    void printAscending(TreeNode* node)//uses iostream
    {
        if (nullptr != node)
        {
            printAscending(node->left);
            printAscending(node->right);
            std::cout << node->value << " ";
        }
    }

    void printDescending(TreeNode* node)//uses iostream
    {
        if (nullptr != node)
        {
            std::cout << node->value << " ";
            printDescending(node->left);
            printDescending(node->right);
        }
    }

    void printForDebug(TreeNode* node)//uses iostream
    {
        using std::cout;
        if (nullptr == node)
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
