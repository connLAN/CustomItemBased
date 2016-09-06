#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

#if(1)
    MainWindow w;
    w.show();
#else
    YuzzViewerWidget v;
    v.show();
#endif

    return a.exec();
}
