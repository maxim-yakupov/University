#pragma once
#include "mathnode.h"

class Sum : public MathNode
{
public:
    Sum(MathNode* l, MathNode* r);
    ~Sum();
    double compute();
    void print();
};
