#pragma once
#include "mathnode.h"

class Num : public MathNode
{
public:
    /**
     * @brief Num Constructor
     * @param v Number
     */
    Num(double v);
    ~Num();
    double compute();
    void print();
private:
    double value;
};
