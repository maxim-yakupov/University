TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += main.cpp \
    outputter.cpp \
    consoleoutputter.cpp \
    fileoutputter.cpp

HEADERS += \
    outputter.h \
    consoleoutputter.h \
    fileoutputter.h

