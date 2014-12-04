#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T13:24:17
#
#-------------------------------------------------

QT       += qml quick widgets

TARGET = Schiffe
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    battleships.cpp \
    board.cpp \
    ship.cpp \
    consoleinterface.cpp \
    gameboardmodel.cpp

HEADERS += \
    battleships.h \
    board.h \
    ship.h \
    consoleinterface.h \
    Utilities.h \
    gameboardmodel.h

OTHER_FILES +=

RESOURCES += \
    QML.qrc
