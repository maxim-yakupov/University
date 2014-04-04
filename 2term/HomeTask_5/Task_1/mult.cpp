#include "mult.h"
#include <iostream>

Mult::Mult(MathNode *l, MathNode *r)
{
    left = l;
    right = r;
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
