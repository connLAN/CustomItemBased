#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T11:50:48
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLPixmapViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    PixmapWidget.cpp

HEADERS  += mainwindow.h \
    PixmapWidget.h \
    structs.h

FORMS    += mainwindow.ui

RESOURCES += \
    textures.qrc
