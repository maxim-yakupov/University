TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    cycled_lists_mod.cpp

HEADERS += \
    cycled_lists_mod.h

