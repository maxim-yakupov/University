CONFIG += c++11

QT       += core gui
QT       += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Task_2
TEMPLATE = app


SOURCES += main.cpp \
	bashimviewer.cpp \
	bashquote.cpp

HEADERS  += \
	bashimviewer.h \
	bashquote.h

FORMS    += \
	bashimviewer.ui \
	bashquote.ui
