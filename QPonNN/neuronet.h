#ifndef NEURONET_H
#define NEURONET_H

#include "layer.h"
#include "synapse.h"
#include "synapseslayer.h"
#include "iactivationfunc.h"
#include <QList>

namespace QPonNN {
    class NeuroNet
    {
    public:
        NeuroNet(unsigned int inputSize);
        void input(QList<double>* in);
        QList<double>* output();
        NeuroNet& appendLayer(IActivationFunc* aFunc, unsigned int size);
        QList<Layer*>* getLayers();
        QList<SynapsesLayer*>* getSynapsesLayers();
        void printConfig();
    private:
        QList<Layer*>* layers;
        QList<SynapsesLayer*>* synapsesLayers;

        class Constant : public IActivationFunc
        {
        public:
            Constant(double v);
            double eval(double x);
            double derivative(double x);
            void setConstant(double v);
            Constant *clone();
        private:
            double value;
        };

        class InputLayer : public Layer
        {
        public:
            InputLayer(unsigned int size);
            void setInput(QList<double>* in);
        };
    };
}

#endif // NEURONET_H
