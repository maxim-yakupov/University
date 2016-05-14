TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core

CONFIG += c++11

SOURCES += main.cpp \
    neuron.cpp \
    synapse.cpp \
    iactivationfunc.cpp \
    sigmoid.cpp \
    layer.cpp \
    neuronet.cpp \
    synapseslayer.cpp \
    backpropagationlearning.cpp \
    biasneuron.cpp

HEADERS += \
    neuron.h \
    synapse.h \
    iactivationfunc.h \
    sigmoid.h \
    QPonNN.h \
    layer.h \
    neuronet.h \
    synapseslayer.h \
    backpropagationlearning.h \
    biasneuron.h

