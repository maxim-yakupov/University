TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += main.cpp \
    heapsorter.cpp \
    quicksorter.cpp \
    randomsorter.cpp

HEADERS += \
    sorter.h \
    heapsorter.h \
    quicksorter.h \
    randomsorter.h

