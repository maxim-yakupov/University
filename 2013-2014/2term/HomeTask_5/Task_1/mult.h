#pragma once
#include "mathnode.h"

class Mult : public MathNode
{
public:
    /**
     * @brief Mult Constructor
     * @param l Left branch
     * @param r Right branch
     */
    Mult(MathNode* l, MathNode* r);
    ~Mult();
    double compute();
    void print();
};
