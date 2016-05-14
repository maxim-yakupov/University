#ifndef BIASNEURON_H
#define BIASNEURON_H

#include "neuron.h"

namespace QPonNN {
    class BiasNeuron : public Neuron
    {
    public:
        BiasNeuron(IActivationFunc* activationFunc);
        double activate();
    };
}
#endif // BIASNEURON_H
