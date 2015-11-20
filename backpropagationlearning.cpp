#include "backpropagationlearning.h"
#include <iostream>

using namespace QPonNN;

BackPropagationLearning::BackPropagationLearning(NeuroNet *nn, double speedOfLearning, double maxError)
    : nn(nn), learningSpeed(speedOfLearning), maxError(maxError)
{
    trainInput = nullptr;
    trainOutput = nullptr;
}


void BackPropagationLearning::setTrainingSet(QList<QList<double>*> *input, QList<QList<double>*> *output)
{
    trainInput = input;
    trainOutput = output;
    clearDZ();
}

void BackPropagationLearning::train(unsigned int maxEpoches)
{
    if (maxEpoches == 0) return;
    double sumError = 0.0;
    for (int trainN = 0; trainN < trainInput->size(); trainN++)
    {
        nn->input(trainInput->at(trainN));
        sumError += metrix(nn->output(), trainOutput->at(trainN));
    }
    unsigned int epoche = 0;
    for (epoche = 0; epoche < maxEpoches; epoche++)
    {
        //nn->printConfig();
        if (epoche % 10 == 0) std::cout << "Epoche " << epoche << ": sumError = " << sumError << std::endl;
        if (sumError < maxError)
        {
            break;
        }
        sumError = 0.0;
        for (int trainN = 0; trainN < trainInput->size(); trainN++)
        {
            nn->input(trainInput->at(trainN));
            QList<double>* outputN = nn->output();
            //
            //output layer
            QList<Neuron*>* outputLayer = nn->getLayers()->last()->getNeurons();
            for (Neuron* n : *outputLayer)
            {
                unsigned int neuronN = outputLayer->indexOf(n);
                n->dZ = (-1.0) * (trainOutput->at(trainN)->at(neuronN) - outputN->at(neuronN)) *
                        n->getActivationFunc()->derivative(n->getPower());//TODO : make beauty
            }
            delete outputN;

            //hidden layers
            for (unsigned int layerN = nn->getLayers()->size() - 2; layerN > 0; layerN--)
            {
                for (Synapse* s : *nn->getSynapsesLayers()->at(layerN)->getSynapses())
                {//TODO : make beauty
                    s->getFrom()->dZ += s->getFrom()->getActivationFunc()->derivative(
                                s->getFrom()->getPower()
                                ) *
                            s->getWeight() * s->getTo()->dZ;
                }
            }
            //
            applyWeightsChanges();
            outputN = nn->output();
            sumError += metrix(outputN, trainOutput->at(trainN));
            delete outputN;
        }
    }
    std::cout << "Last epoche: " << epoche << " sumError = " << sumError << std::endl;
}

double BackPropagationLearning::metrix(QList<double> *realOutput, QList<double> *output)
{
    double res = 0.0;
    for (int i = 0; i < output->size(); i++)
    {
        double delta = realOutput->at(i) - output->at(i);
        res += delta * delta;
    }
    return res / 2.0;
}

void BackPropagationLearning::clearDZ()
{
    bool firstInputLayerSkipped = false;
    for (Layer* l : *nn->getLayers())
    {
        if (!firstInputLayerSkipped)
        {
            firstInputLayerSkipped = true;
            continue;
        }
        for (Neuron* n : *l->getNeurons())
        {
            n->dZ = 0.0;
        }
    }
}

void BackPropagationLearning::applyWeightsChanges()
{
    for (SynapsesLayer* sl : *nn->getSynapsesLayers())
    {
        for (Synapse* s : *sl->getSynapses())
        {
            s->setWeight(s->getWeight() -
                         learningSpeed *
                         s->getTo()->dZ *
                         s->getFrom()->activate()
                        );
        }
    }
    clearDZ();
}
