TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

QT += core
QT += testlib

SOURCES += main.cpp

HEADERS += \
    sorter.h \
    comparator.h \
    testSorter.h

