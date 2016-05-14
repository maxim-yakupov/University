#ifndef BACKPROPAGATIONLEARNING_H
#define BACKPROPAGATIONLEARNING_H

#include "neuronet.h"
#include <QList>

namespace QPonNN {
    class BackPropagationLearning
    {
    public:
        BackPropagationLearning(NeuroNet* nn, double speedOfLearning, double maxError);
        void setTrainingSet(QList<QList<double> *> *input, QList<QList<double> *> *output);
        void train(unsigned int maxEpoches);
    private:
        NeuroNet* nn;
        QList<QList<double>*>* trainInput;
        QList<QList<double>*>* trainOutput;
        double learningSpeed;
        double maxError;

        double metrix(QList<double> *realOutput, QList<double> *output);
        void clearDZ();
        void applyWeightsChanges();
    };
}

#endif // BACKPROPAGATIONLEARNING_H
