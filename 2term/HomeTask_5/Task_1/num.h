#pragma once
#include "mathnode.h"

class Num : public MathNode
{
public:
    Num(double v);
    ~Num();
    double compute();
    void print();
private:
    double value;
};
