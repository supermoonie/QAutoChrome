#-------------------------------------------------
#
# Project created by QtCreator 2018-12-03T10:43:51
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QAutoChrome
TEMPLATE = app

CONFIG += C++11

SOURCES += main.cpp\
        mainwindow.cpp \
    page.cpp \
    launcher.cpp \
    qautochrome.cpp \
    websocketadapter.cpp \
    websocketcontext.cpp

HEADERS  += mainwindow.h \
    page.h \
    launcher.h \
    qautochrome.h \
    websocketadapter.h \
    websocketcontext.h

FORMS    += mainwindow.ui
