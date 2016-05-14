#ifndef SYNAPSE_H
#define SYNAPSE_H

//#include "neuron.h"

namespace QPonNN {
    //
    class Neuron;

    class Synapse
    {
    public:
        Synapse(Neuron* from, Neuron* to, double weight);
        double getWeight() const;
        void setWeight(double value);
        void impulse();
        Neuron *getFrom() const;
        Neuron *getTo() const;
    private:
        Neuron* from;
        Neuron* to;
        double weight;
    };
}

#endif // SYNAPSE_H
