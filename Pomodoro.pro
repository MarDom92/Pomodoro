#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T11:44:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pomodoro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    settings.h

FORMS    += mainwindow.ui \
    settings.ui
