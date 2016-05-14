#pragma once

namespace BinaryTreeAPI
{
    struct TreeNode
    {
        int value;
        char letter;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
    };
    struct Tree
    {
        TreeNode* root;
    };

    Tree create();
    TreeNode* createNode(int value, char letter);
    bool isLeaf(TreeNode* node);
    bool addValue(TreeNode *&currentNode, int value, char letter);
    void cleanUp(Tree& tree);
}
