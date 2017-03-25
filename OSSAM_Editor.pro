#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T18:19:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSSAM_Editor
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    SpaceShip_Editor/SpaceshipEditor.cpp

HEADERS  += MainWindow.h \
    SpaceShip_Editor/SpaceshipEditor.h

FORMS    += MainWindow.ui \
    SpaceShip_Editor/SpaceshipEditor.ui
