#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T11:08:41
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialCommunication
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    workerthread.cpp \
    workerthread_2.cpp

HEADERS  += mainwindow.h \
    workerthread.h \
    workerthread_2.h

FORMS    += mainwindow.ui
