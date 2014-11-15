#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T23:49:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CineFeel
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    APIConnector.cpp

HEADERS  += MainWindow.h \
    APIConnector.h

FORMS    += MainWindow.ui
