TEMPLATE = subdirs

SUBDIRS += \
    CustomItemMonitor/CustomItemMonitor \
    YuzzViewer/YuzzViewer

#YuzzViewer.depends = CustomItemMonitor/CustomItemMonitor

OTHER_FILES += \
    CustomItemBased.pri
