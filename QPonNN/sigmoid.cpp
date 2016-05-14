#include "sigmoid.h"
#include <math.h>
#include <iostream>//

double Sigmoid::eval(double x)
{
    //std::cout << "Sigmoid(" << x << ")= " << 1 / (1 + exp(-x)) << "\n";
    return 1 / (1 + exp(-x));
}

double Sigmoid::derivative(double x)
{
    return eval(x) * (1 - eval(x));
}

Sigmoid *Sigmoid::clone()
{
    return new Sigmoid();
}
