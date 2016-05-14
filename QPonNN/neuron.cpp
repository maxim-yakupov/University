#include "neuron.h"
#include "synapse.h"

using namespace QPonNN;

Neuron::Neuron(IActivationFunc *activationFunc)
{
    aFunc = activationFunc;
    incomeSynapses = new QList<Synapse*>();
    resetPower();
}

IActivationFunc* Neuron::getActivationFunc()
{
    return aFunc;
}

double Neuron::activate()
{
    double res = aFunc->eval(power);
    return (res < 0.0 ? 0.0 : res);
}

void Neuron::addPower(double delta)
{
    power += delta;
}

void Neuron::resetPower()
{
    power = 0.0;
}

void Neuron::assignIncomeSynapse(Synapse *s)
{
    incomeSynapses->append(s);
}
