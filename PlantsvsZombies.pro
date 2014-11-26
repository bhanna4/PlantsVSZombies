#-------------------------------------------------
#
# Project created by QtCreator 2014-11-11T14:30:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PlantsvsZombies
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lawn.cpp \
    plants.cpp \
    username.cpp \
    sunshine.cpp \
    zombie.cpp

HEADERS  += mainwindow.h \
    lawn.h \
    plants.h \
    username.h \
    sunshine.h \
    zombie.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resource.qrc
