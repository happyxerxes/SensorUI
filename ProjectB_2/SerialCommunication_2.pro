#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T16:16:25
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialCommunication_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workerthread.cpp

HEADERS  += mainwindow.h \
    workerthread.h

FORMS    += mainwindow.ui
