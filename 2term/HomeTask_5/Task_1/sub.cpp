#include "sub.h"
#include <iostream>

Sub::Sub(MathNode *l, MathNode *r)
{
    left = l;
    right = r;
}

Sub::~Sub()
{
    delete left;
    delete right;
}

double Sub::compute()
{
    return (left->compute() - right->compute());
}

void Sub::print()
{
    std::cout << "(";
    left->print();
    std::cout << "-";
    right->print();
    std::cout << ")";
}
