#pragma once
#include "mathnode.h"

/**
 * @brief The MathTree class
 */
class MathTree
{
public:
    /**
     * @brief operator () Converts expression string to tree
     * @param inStr Expression string
     */
    void operator()(char* inStr);
    MathTree();
    MathTree(char* incomeExpr);
    ~MathTree();
    /**
     * @brief print Writes tree in 'expression view'
     */
    void print();
    /**
     * @brief compute Calculates expression from the tree
     * @return Result of calculation
     */
    double compute();
private:
    MathNode* root;
    unsigned int curPos;

    int strlen(char* str);
    double readDoubleFromStr(char *str);
    MathNode* makeTree(char* str);
};
