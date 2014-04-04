#pragma once
#include "mathnode.h"

class MathTree
{
public:
    void operator()(char* inStr);
    MathTree(char* incomeExpr);
    ~MathTree();
    void print();
    double compute();
private:
    MathNode* root;
    unsigned int curPos;

    int strlen(char* str);
    double readDoubleFromStr(char *str);
    MathNode* makeTree(char* str);
};
