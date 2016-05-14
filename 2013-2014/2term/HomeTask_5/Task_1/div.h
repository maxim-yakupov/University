#pragma once
#include "mathnode.h"

class Div : public MathNode
{
public:
    /**
     * @brief Div Constructor
     * @param l Left branch
     * @param r Right branch
     */
    Div(MathNode* l, MathNode* r);
    ~Div();
    double compute();
    void print();
};
