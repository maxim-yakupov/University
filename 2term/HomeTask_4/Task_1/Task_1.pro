TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core
QT += testlib

CONFIG += c++11

SOURCES += main.cpp \
    hashtable.cpp \
    list.cpp \
    singlylinkedlist.cpp \
    uniquelist.cpp

HEADERS += \
    hashtable.h \
    list.h \
    singlylinkedlist.h \
    uniquelist.h \
    testHashTable.h

