#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T09:38:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnnotionTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myview.cpp \
    customitem.cpp

HEADERS  += mainwindow.h \
    myview.h \
    customitem.h

FORMS    += mainwindow.ui
