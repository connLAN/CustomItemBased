#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    ui->frame_Viewer->slotInitialize(layersNumber,stripesNumber,channelsNumber,0,BANANA_INFO()/*{0,0,730,1500,0,1.57,0,0,0}*/);
    //connect(this,SIGNAL(signalDataReady(int,int,int,QStringList,QPixmap)),ui->frame_Viewer,SLOT(slotUpdate(int,int,int,QStringList,QPixmap)));
    connect(this,SIGNAL(signalDataReady(int,int,int,QStringList,QImage)),ui->frame_Viewer,SLOT(slotUpdate(int,int,int,QStringList,QImage)));
    connect(timer,SIGNAL(timeout()),this, SLOT(slotDataPreparing()));
    timer->start(5);
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete ui;
}

void MainWindow::slotDataPreparing()
{
    static int layer=0;
    static int stripe=0;
    static int channel=0;
    QStringList description;
    QPixmap pixmap;
    QString path;
    QImage image_src;
    QImage image;

    //path=QString(":/res/res/Layer%1_stripe%2_channel%3_dump.bmp").arg(layer,4,10,QChar('0')).arg(stripe,2,10,QChar('0')).arg(channel);
    //path=QString(":/res/res/Layer%1_stripe%2_channel0_dump.bmp").arg(layer,4,10,QChar('0')).arg(stripe,2,10,QChar('0'));
      path=QString(":/res/res/Layer%1_stripe%2_channel%3_dump.bmp").arg(layer,4,10,QChar('0')).arg(stripe,2,10,QChar('0')).arg(channel);
//qDebug()<< path;
    //path=QString(":/res/res/test%1.bmp").arg(layer&3);

    //pixmap.load(path);
    //mPixmaps.push_back(pixmap);

    //image.load(path);

    image_src.load(path);
    image = image_src.convertToFormat(QImage::Format_Mono);

    //mImages.push_back(image);


    //pixmap = pixmap.fromImage(image_dst);
    //pixmap = pixmap.fromImage(image);

    //QMatrix rm;
    //rm.rotate(90);
    //pixmap = pixmap.transformed(rm);

    description << path;
    for(int i = 0; i < 100; i++)
        description << QString("[%1] description:  layer=%2 stripe=%3 channel=%4").arg(i).arg(layer).arg(stripe).arg(channel);

    //emit signalDataReady(layer,stripe,channel,description,pixmap);
    emit signalDataReady(layer,stripe,channel,description,image);

    ++channel;
    if(channel==channelsNumber)
    {
        channel=0;
        ++stripe;
        if(stripe==stripesNumber)
        {
            stripe=0;
            ++layer;
            if(layer==layersNumber)
            {
                layer=0;
                timer->stop();
                //ui->frame_Viewer->slotInitialize(layersNumber,stripesNumber,channelsNumber);
            }
        }
    }
}
