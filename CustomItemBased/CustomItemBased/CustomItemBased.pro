TEMPLATE = subdirs

SUBDIRS += \
    CustomItemMonitor/CustomItemMonitor \
    YuzzViewer/YuzzViewer \
    GLPixmapViewer/GLPixmapViewer

#YuzzViewer.depends = CustomItemMonitor/CustomItemMonitor

OTHER_FILES += \
    CustomItemBased.pri
