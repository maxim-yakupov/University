#include "biasneuron.h"
#include <iostream>//

QPonNN::BiasNeuron::BiasNeuron(QPonNN::IActivationFunc *activationFunc)
    : Neuron(activationFunc)
{
    addPower(1.0);
}

double QPonNN::BiasNeuron::activate()
{
    //std::cout << "bias\n";
    return 1;
}
