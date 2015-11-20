#include "neuronet.h"
#include <iostream>//
using namespace QPonNN;

NeuroNet::NeuroNet(unsigned int inputSize)
{
    layers = new QList<Layer*>();
    layers->append(new InputLayer(inputSize));
    synapsesLayers = new QList<SynapsesLayer*>();
}

void NeuroNet::input(QList<double> *in)
{
    for (Layer* l : *layers)
    {
        for (Neuron* n : *l->getNeurons())
        {
            n->resetPower();
        }
    }
    ((InputLayer*) layers->first())->setInput(in);
}

QList<double> *NeuroNet::output()
{
    for (Layer* l : *layers)
    {
        for (Neuron* n : *l->getNeurons())
        {
            n->resetPower();
        }
    }
    for (SynapsesLayer* sl : *synapsesLayers)
    {
        //std::cout << "synapseLayer impulse\n";//
        sl->impulseAll();
    }
    //
    for (Layer* l : *layers)
    {
        l->writeNeuronsPowers();
    }
    //
    QList<double>* out = new QList<double>();
    for (Neuron* n : *layers->last()->getNeurons())
    {
        out->append(n->activate());
    }
    return out;
}

NeuroNet &NeuroNet::appendLayer(IActivationFunc *aFunc, unsigned int size)
{
    Layer* prevLast = layers->last();
    layers->append(new Layer(aFunc, size));
    synapsesLayers->append(new SynapsesLayer(prevLast, layers->last()));
    return *this;
}

QList<Layer *> *NeuroNet::getLayers()
{
    return layers;
}

QList<SynapsesLayer *> *NeuroNet::getSynapsesLayers()
{
    return synapsesLayers;
}

void NeuroNet::printConfig()
{
    std::cout << "\nConfig: ";
    for (Layer* l : *layers)
    {
        std::cout << "[" << l->getNeurons()->size() << "]";
    }
    for (SynapsesLayer* l : *synapsesLayers)
    {
        std::cout << "\n{";
        for (Synapse* s : *l->getSynapses())
        {
            std::cout << s->getWeight() << ", ";
        };
        std::cout << "}";
    }
    std::cout << "\n";
}


NeuroNet::Constant::Constant(double v) : value(v)
{
}

double NeuroNet::Constant::eval(double x)
{
    //std::cout << "Constant(" << x << ")= " << value << "\n";
    return value;
}

double NeuroNet::Constant::derivative(double x)
{
    UNUSED_VAR(x);
    return 0;
}

void NeuroNet::Constant::setConstant(double v)
{
    value = v;
}

NeuroNet::Constant *NeuroNet::Constant::clone()
{
    return new Constant(value);
}

NeuroNet::InputLayer::InputLayer(unsigned int size) : Layer(new Constant(0.0), size)
{
}

void NeuroNet::InputLayer::setInput(QList<double> *in)
{
    for (int i = 0; i < in->size(); i++)
    {
        ((NeuroNet::Constant*) getNeurons()->at(i)->getActivationFunc())
                ->setConstant(
                    in->at(i)
                    );
    }
}
