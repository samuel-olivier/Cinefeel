#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T23:51:45
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestAnalyseMoyenneVideo
TEMPLATE = app


SOURCES += main.cpp \
    videodebugger.cpp \
    APIConnector.cpp \
    color.cpp

HEADERS  += \
    videodebugger.h \
    APIConnector.h \
    color.h

FORMS    += \
    form.ui
