#include "iactivationfunc.h"
#include <iostream>//

using namespace QPonNN;

double IActivationFunc::eval(double x)
{
    std::cout << "IActivationFunc\n";
    return x;
}

double IActivationFunc::derivative(double x)
{
    UNUSED_VAR(x);
    return 1;
}

IActivationFunc *IActivationFunc::clone()
{
    return new IActivationFunc();
}
