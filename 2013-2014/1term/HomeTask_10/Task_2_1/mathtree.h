#pragma once

namespace MathTreeAPI
{
    struct MathNode
    {
        double value;
        char operation;
        MathNode* left;
        MathNode* right;
        MathNode* parent;
    };
    struct MathTree
    {
        MathNode* root;
    };

    MathTree create();
    void add(MathNode*& node, double value, char operation);
    void cleanUp(MathTree& tree);
    void printForDebug(MathNode* node);
}
