#pragma once
#include "mathnode.h"

class Mult : public MathNode
{
public:
    Mult(MathNode* l, MathNode* r);
    ~Mult();
    double compute();
    void print();
};
