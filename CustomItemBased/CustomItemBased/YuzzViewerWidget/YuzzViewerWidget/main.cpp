#include "YuzzViewerWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YuzzViewerWidget w;
    w.show();

    return a.exec();
}
