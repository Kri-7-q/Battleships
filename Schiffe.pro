#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T13:24:17
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Schiffe
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    battleships.cpp \
    board.cpp \
    ship.cpp \
    consoleinterface.cpp

HEADERS += \
    battleships.h \
    board.h \
    ship.h \
    consoleinterface.h \
    Utilities.h
