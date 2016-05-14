#include "mult.h"
#include <iostream>

Mult::Mult(MathNode *l, MathNode *r) : MathNode(l, r)
{
}

Mult::~Mult()
{
    delete left;
    delete right;
}

double Mult::compute()
{
    return (left->compute() * right->compute());
}

void Mult::print()
{
    std::cout << "(";
    left->print();
    std::cout << "*";
    right->print();
    std::cout << ")";
}
