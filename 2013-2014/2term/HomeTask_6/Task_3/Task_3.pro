TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core
QT += testlib

CONFIG += c++11

SOURCES += main.cpp

HEADERS += \
    sharedpointer.h \
    testSharedPointer.h

