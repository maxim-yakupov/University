TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    maxstring.cpp \
    lists_mod.cpp \
    binarytree.cpp

HEADERS += \
    maxstring.h \
    lists_mod.h \
    binarytree.h

