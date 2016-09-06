#-------------------------------------------------
#
# Project created by QtCreator 2016-09-05T14:56:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = YuzzViewerWidget
TEMPLATE = app
INCLUDEPATH +=../../CustomItemMonitor/CustomItemMonitor/
INCLUDEPATH +=../../GLPixmapViewer/GLPixmapViewer/

SOURCES += main.cpp\
        YuzzViewerWidget.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItem.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemData.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemDelegate.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTableModel.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTableMonitor.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTableView.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTreeModel.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTreeMonitor.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTreeView.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemWidget.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemWidgets.cpp \
    ../../CustomItemMonitor/CustomItemMonitor/qcustomplot.cpp \
    YuzzViewer.cpp \
    ../../GLPixmapViewer/GLPixmapViewer/PixmapWidget.cpp

HEADERS  += YuzzViewerWidget.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItem.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemData.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemDelegate.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTableModel.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTableMonitor.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTableView.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTreeModel.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTreeMonitor.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTreeView.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemTypes.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemWidget.h \
    ../../CustomItemMonitor/CustomItemMonitor/CustomItemWidgets.h \
    ../../CustomItemMonitor/CustomItemMonitor/qcustomplot.h \
    YuzzViewer.h \
    ../../GLPixmapViewer/GLPixmapViewer/PixmapWidget.h \
    ../../GLPixmapViewer/GLPixmapViewer/structs.h

FORMS    += YuzzViewerWidget.ui
