#include "SliceViewerWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SliceViewerWidget w;
    w.show();

    return a.exec();
}
