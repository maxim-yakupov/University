#include "synapse.h"
#include <iostream>//
#include "neuron.h"

using namespace QPonNN;

Synapse::Synapse(Neuron *from, Neuron *to, double weight) : from(from), to(to), weight(weight)
{
}

double Synapse::getWeight() const
{
    return weight;
}

void Synapse::setWeight(double value)
{
    weight = value;
}

void Synapse::impulse()
{
    //std::cout << "(" << this->from->getPower() << "---" << this->weight << "---" << this->to->getPower() << ")\n";
    to->addPower(from->activate() * weight);
}

Neuron *Synapse::getFrom() const
{
    return from;
}

Neuron *Synapse::getTo() const
{
    return to;
}

