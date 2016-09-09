#include "SliceViewerWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SliceViewerWidget w;

    w.show();
    w.test();

    return a.exec();
}
