#pragma once
#include "mathnode.h"

class Div : public MathNode
{
public:
    Div(MathNode* l, MathNode* r);
    ~Div();
    double compute();
    void print();
//protected:
//    MathNode* left;
//    MathNode* right;
};
