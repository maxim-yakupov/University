#ifndef SYNAPSESLAYER_H
#define SYNAPSESLAYER_H

#include "layer.h"
#include "synapse.h"
#include <QList>

namespace QPonNN {
    class SynapsesLayer
    {
    public:
        SynapsesLayer(Layer* from, Layer* to);
        QList<Synapse*>* getSynapses() const;
        void impulseAll();
    private:
        QList<Synapse*>* synapses;
    };
}

#endif // SYNAPSESLAYER_H
