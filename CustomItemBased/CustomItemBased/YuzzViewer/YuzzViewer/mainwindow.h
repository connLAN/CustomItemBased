#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QPixmap>
#include <QImage>
#include <QVector>
#include <QImage>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotDataPreparing();
signals:
    void signalDataReady(int layer, int stripe, int channel,const QStringList& description,const QPixmap& pixmap);
    void signalDataReady(int layer, int stripe, int channel,const QStringList& description,const QImage& image);
private:
    QTimer* timer;
    Ui::MainWindow *ui;
    int layersNumber{2};
    int stripesNumber{1};
    int channelsNumber{2};
    QVector<QImage> mImages;
    QVector<QPixmap> mPixmaps;
};

#endif // MAINWINDOW_H
