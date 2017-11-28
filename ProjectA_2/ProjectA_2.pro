#-------------------------------------------------
#
# Project created by QtCreator 2017-10-05T10:45:57
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectA_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workerthread.cpp

HEADERS  += mainwindow.h \
    workerthread.h

FORMS    += mainwindow.ui
