TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

QT += core
QT += testlib

CONFIG += c++11

SOURCES += main.cpp \
    doublylinkedlist.cpp \
    list.cpp \
    singlylinkedlist.cpp

HEADERS += \
    doublylinkedlist.h \
    list.h \
    singlylinkedlist.h \
    testList.h

