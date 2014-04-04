TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

#QT += core \
#    testlib

CONFIG += c++11

SOURCES += main.cpp \
    mathtree.cpp \
    div.cpp \
    sum.cpp \
    mult.cpp \
    sub.cpp \
    num.cpp

HEADERS += \
    mathnode.h \
    mathtree.h \
    div.h \
    sum.h \
    mult.h \
    sub.h \
    num.h

