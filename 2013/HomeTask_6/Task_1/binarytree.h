#pragma once

namespace BinaryTreeAPI
{
    struct TreeNode
    {
        int value;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
    };
    struct Tree
    {
        TreeNode* root;
    };

    Tree create();
    bool isLeaf(TreeNode* node);
    bool addValue(TreeNode *&currentNode, int value);
    bool removeValue(Tree &tree, int value);
    bool exists(Tree &tree, int value);
    void cleanSubtree(TreeNode*& node);
    void cleanUp(Tree& tree);
    void printAscending(TreeNode *node);
    void printDescending(TreeNode *node);
    void printForDebug(TreeNode* node);
}
