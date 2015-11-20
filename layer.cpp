#include "layer.h"
#include <iostream>//

using namespace QPonNN;

Layer::Layer(IActivationFunc *activationFunc, unsigned int amount) : neuronsNumber(amount)
{
    neurons = new QList<Neuron*>();
    for (unsigned int i = 0; i < amount; i++)
    {
        neurons->append(new Neuron(activationFunc->clone()));
    }
    bias = new BiasNeuron(activationFunc->clone());
}

QList<Neuron *> *Layer::getNeurons() const
{
    return neurons;
}

BiasNeuron *Layer::getBias() const
{
    return bias;
}

void Layer::writeNeuronsPowers()
{
    for (Neuron* n : *neurons)
    {
        //std::cout << "nPower: " << n->getPower() << "\n";
    }
}
