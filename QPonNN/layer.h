#ifndef LAYER_H
#define LAYER_H

#include "iactivationfunc.h"
#include "neuron.h"
#include "biasneuron.h"
#include <QList>

namespace QPonNN {
    class Layer
    {
    public:
        Layer(IActivationFunc* activationFunc, unsigned int amount);
        QList<Neuron*>* getNeurons() const;
        BiasNeuron* getBias() const;
        void writeNeuronsPowers();//
    private:
        unsigned int neuronsNumber;
        QList<Neuron*>* neurons;
        BiasNeuron* bias;
    };
}
#endif // LAYER_H
