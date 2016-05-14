#-------------------------------------------------
#
# Project created by QtCreator 2014-05-09T08:52:50
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Task_3
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    crossesandzeros.cpp \
    crossesandzeroslogic.cpp \
    crossesandzeroslogicpv.cpp

HEADERS  += \
    crossesandzeros.h \
    crossesandzeroslogic.h \
    testCrossesAndZerosLogic.h \
    crossesandzeroslogicpv.h

FORMS    += \
    crossesandzeros.ui \
    crossesandzeroslogic.ui
