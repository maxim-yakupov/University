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
    void printExpression(MathNode* node, int fl);
    void add(MathNode*& node, double value, char operation);
    double calculateExpression(MathNode*& node);
    void cleanUp(MathTree& tree);
    void printForDebug(MathNode* node);
}
