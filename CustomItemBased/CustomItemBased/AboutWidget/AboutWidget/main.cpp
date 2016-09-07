#include "AboutWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AboutWidget w;
    w.show();

    return a.exec();
}
