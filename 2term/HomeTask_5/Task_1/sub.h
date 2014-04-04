#pragma once
#include "mathnode.h"

class Sub : public MathNode
{
public:
    Sub(MathNode* l, MathNode* r);
    ~Sub();
    double compute();
    void print();
};
