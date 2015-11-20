#ifndef SIGMOID_H
#define SIGMOID_H

#include "QPonNN.h"

class Sigmoid : public QPonNN::IActivationFunc
{
public:
    double eval(double x);
    double derivative(double x);
    Sigmoid *clone();
};

#endif // SIGMOID_H
