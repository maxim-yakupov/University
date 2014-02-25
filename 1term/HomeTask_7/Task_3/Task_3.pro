TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    maxstring.cpp \
    hashtable.cpp

HEADERS += \
    maxstring.h \
    hashtable.h
