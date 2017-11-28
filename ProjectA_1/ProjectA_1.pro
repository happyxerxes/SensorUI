#-------------------------------------------------
#
# Project created by QtCreator 2017-10-04T11:19:49
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectA_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workerthread.cpp \
    workerthread_2.cpp

HEADERS  += mainwindow.h \
    workerthread.h \
    workerthread_2.h

FORMS    += mainwindow.ui

RESOURCES +=

DISTFILES +=
