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
    connectwindow.cpp \
    sock.cpp \
    boardwindow.cpp

HEADERS  += \
    sock.h \
    connectwindow.h \
    boardwindow.h

FORMS    += \
    connectwindow.ui \
    boardwindow.ui
CONFIG += c++11

RESOURCES += \
    resources.qrc

