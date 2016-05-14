#pragma once
#include "mathnode.h"

class Sub : public MathNode
{
public:
    /**
     * @brief Sub Constructor
     * @param l Left branch
     * @param r Right branch
     */
    Sub(MathNode* l, MathNode* r);
    ~Sub();
    double compute();
    void print();
};
