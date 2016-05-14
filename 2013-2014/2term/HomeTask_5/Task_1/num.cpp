#include "num.h"
#include <iostream>

Num::Num(double v) : MathNode(nullptr, nullptr)
{
    value = v;
}

Num::~Num()
{
}

double Num::compute()
{
    return value;
}

void Num::print()
{
    std::cout << value;
}
