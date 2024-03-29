#-------------------------------------------------
#
# Project created by QtCreator 2016-08-23T12:26:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = YuzzViewer
TEMPLATE = app
INCLUDEPATH +=../../YuzzViewerWidget/YuzzViewerWidget/
INCLUDEPATH +=../../CustomItemMonitor/CustomItemMonitor/
INCLUDEPATH +=../../GLPixmapViewer/GLPixmapViewer/

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../YuzzViewerWidget/YuzzViewerWidget/YuzzViewerWidget.cpp \
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
    ../../GLPixmapViewer/GLPixmapViewer/PixmapWidget.cpp \
    ../../YuzzViewerWidget/YuzzViewerWidget/YuzzViewer.cpp

HEADERS  += mainwindow.h \
    ../../YuzzViewerWidget/YuzzViewerWidget/YuzzViewerWidget.h \
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
    ../../GLPixmapViewer/GLPixmapViewer/PixmapWidget.h \
    ../../GLPixmapViewer/GLPixmapViewer/structs.h \
    ../../YuzzViewerWidget/YuzzViewerWidget/YuzzViewer.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc



