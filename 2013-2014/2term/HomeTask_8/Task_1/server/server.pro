CONFIG += c++11

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp \
    server.cpp

HEADERS  += \
    server.h

FORMS    += \
    server.ui
