TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core
QT += testlib

CONFIG += c++11

SOURCES += main.cpp \
    list.cpp \
    singlylinkedlist.cpp \
    uniquelist.cpp

HEADERS += \
    list.h \
    singlylinkedlist.h \
    uniquelist.h \
    exceptions.h \
    testUniqueList.h

