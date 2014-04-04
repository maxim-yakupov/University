#include "num.h"
#include <iostream>

Num::Num(double v)
{
    left = nullptr;
    right = nullptr;
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
