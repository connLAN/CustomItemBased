#-------------------------------------------------
#
# Project created by QtCreator 2016-09-07T17:56:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SliceViewerWidget
TEMPLATE = app
INCLUDEPATH +=../../CustomItemMonitor/CustomItemMonitor/

SOURCES += main.cpp\
        SliceViewerWidget.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/qcustomplot.cpp \
    QCustomPlotExt.cpp

HEADERS  += SliceViewerWidget.h \
    ../../CustomItemMonitor/CustomItemMonitor/qcustomplot.h \
    QCustomPlotExt.h

FORMS    += SliceViewerWidget.ui
