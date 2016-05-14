CONFIG += c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Shtrafnaya
TEMPLATE = app


SOURCES += main.cpp\
    cannon.cpp \
    bullet.cpp \
    gamescene.cpp

HEADERS  += \
    cannon.h \
    bullet.h \
    gamescene.h

FORMS    +=
