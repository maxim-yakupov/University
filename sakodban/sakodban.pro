CONFIG += c++11

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sakodban
TEMPLATE = app


SOURCES += main.cpp \
    gamescene.cpp \
    player.cpp \
    field.cpp \
    tile.cpp

HEADERS  += \
    gamescene.h \
    player.h \
    field.h \
    tile.h \
    gameParams.h

OTHER_FILES +=

RESOURCES += \
    res.qrc
