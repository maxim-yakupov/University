#include "sum.h"
#include <iostream>

Sum::Sum(MathNode *l, MathNode *r) : MathNode(l, r)
{
}

Sum::~Sum()
{
    delete left;
    delete right;
}

double Sum::compute()
{
    return (left->compute() + right->compute());
}

void Sum::print()
{
    std::cout << "(";
    left->print();
    std::cout << "+";
    right->print();
    std::cout << ")";
}
