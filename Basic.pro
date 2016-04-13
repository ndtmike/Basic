#-------------------------------------------------
#
# Project created by QtCreator 2016-03-26T18:37:20
#
#-------------------------------------------------

QT       += core gui serialport widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Basic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    splash.cpp \
    currentserialport.cpp

HEADERS  += mainwindow.h \
    splash.h \
    currentserialport.h

FORMS    += mainwindow.ui \
    splash.ui

RESOURCES += \
    basic.qrc
