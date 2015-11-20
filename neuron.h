#ifndef NEURON_H
#define NEURON_H

#include "iactivationfunc.h"
//#include "synapse.h"
#include <QList>

namespace QPonNN {
    //
    class Synapse;

    class Neuron
    {
    public:
        Neuron(IActivationFunc* activationFunc);
        IActivationFunc* getActivationFunc();
        virtual double activate();
        void addPower(double delta);
        void resetPower();
        double getPower() { return power; }//
        void assignIncomeSynapse(Synapse* s);

        double dZ;
    private:
        IActivationFunc* aFunc;
        QList<Synapse*>* incomeSynapses;
        double power;
    };
}

#endif // NEURON_H
