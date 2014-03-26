TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core
QT += testlib

CONFIG += c++11

SOURCES += main.cpp

HEADERS += \
    stack.h \
    pointerstack.h \
    arraystack.h \
    calculator.h \
    testCalculator.h \
    testStack.h

