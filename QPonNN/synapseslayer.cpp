#include "synapseslayer.h"
#include <iostream>//
using namespace QPonNN;

SynapsesLayer::SynapsesLayer(Layer *from, Layer *to)
{
    synapses = new QList<Synapse*>();
    for (Neuron* f : *from->getNeurons())
    {
        for (Neuron* t : *to->getNeurons())
        {
            Synapse* nSynapse = new Synapse(f, t, 0.5);
            t->assignIncomeSynapse(nSynapse);
            synapses->append(nSynapse);
        }
    }
    for (Neuron* t : *to->getNeurons())
    {
        Synapse* nSynapse = new Synapse(from->getBias(), t, 0.5);
        t->assignIncomeSynapse(nSynapse);
        synapses->append(nSynapse);
    }
}

QList<Synapse *> *SynapsesLayer::getSynapses() const
{
    return synapses;
}

void SynapsesLayer::impulseAll()
{
    for (Synapse* s : *synapses)
    {
        //std::cout << "synapse impulse\n";//
        s->impulse();
    }
}
