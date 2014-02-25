TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    binarytree.cpp \
    lists_mod.cpp \
    maxstring.cpp

HEADERS += \
    binarytree.h \
    lists_mod.h \
    maxstring.h

