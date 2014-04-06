#pragma once
#include "mathnode.h"

class Sum : public MathNode
{
public:
    /**
     * @brief Sum Constructor
     * @param l Left branch
     * @param r Right branch
     */
    Sum(MathNode* l, MathNode* r);
    ~Sum();
    double compute();
    void print();
};
