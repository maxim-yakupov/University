#include "div.h"
#include <iostream>

Div::Div(MathNode *l, MathNode *r) : MathNode(l, r)
{
}

Div::~Div()
{
    delete left;
    delete right;
}

double Div::compute()
{
    return (left->compute() / right->compute());
}

void Div::print()
{
    std::cout << "(";
    left->print();
    std::cout << "/";
    right->print();
    std::cout << ")";
}
