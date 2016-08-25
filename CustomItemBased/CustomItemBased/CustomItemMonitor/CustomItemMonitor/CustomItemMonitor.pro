#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T12:21:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = CustomItemMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CustomItem.cpp \
    CustomItemData.cpp \
    CustomItemDelegate.cpp \
    CustomItemTableModel.cpp \
    CustomItemTableMonitor.cpp \
    CustomItemTableView.cpp \
    CustomItemTreeModel.cpp \
    CustomItemTreeMonitor.cpp \
    CustomItemTreeView.cpp \
    CustomItemWidget.cpp \
    CustomItemWidgets.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    CustomItem.h \
    CustomItemData.h \
    CustomItemDelegate.h \
    CustomItemTableModel.h \
    CustomItemTableMonitor.h \
    CustomItemTableView.h \
    CustomItemTreeModel.h \
    CustomItemTreeMonitor.h \
    CustomItemTreeView.h \
    CustomItemTypes.h \
    CustomItemWidget.h \
    CustomItemWidgets.h \
    qcustomplot.h

FORMS    += mainwindow.ui
