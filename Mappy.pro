#-------------------------------------------------
#
# Project created by QtCreator 2017-10-02T12:23:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mappy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mapeditor.cpp \
    tileset.cpp \
    newmap.cpp \
    mappysaver.cpp \
    about.cpp \
    clickablelabel.cpp

HEADERS  += mainwindow.h \
    mapeditor.h \
    tileset.h \
    newmap.h \
    mappysaver.h \
    about.h \
    clickablelabel.h

FORMS    += mainwindow.ui \
    newmap.ui \
    about.ui

RESOURCES += \
    res.qrc
