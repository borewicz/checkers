#-------------------------------------------------
#
# Project created by QtCreator 2015-11-05T21:20:58
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_MAC_SDK = macosx10.11

TARGET = checkers-client
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
CONFIG += c++11

RESOURCES += \
    resources.qrc

