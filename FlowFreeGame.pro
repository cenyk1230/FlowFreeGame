#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T14:41:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlowFreeGame
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    gamegen.cpp \
    gamegenfromfile.cpp \
    solver.cpp

HEADERS  += widget.h \
    gamegen.h \
    gamegenfromfile.h \
    solver.h

FORMS    += widget.ui
