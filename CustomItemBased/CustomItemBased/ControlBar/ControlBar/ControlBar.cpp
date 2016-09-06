#include <QFileDialog>
#include "ControlBar.h"
#include "ui_ControlBar.h"

ControlBar::ControlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlBar)
{
    ui->setupUi(this);
    init();
}

ControlBar::~ControlBar()
{
    delete ui;
}

void ControlBar::init()
{
    connect(ui->pushButton_Start,       SIGNAL(clicked(bool)), this,   SLOT(slotStartJob()));

    connect(ui->pushButton_Load,        SIGNAL(clicked(bool)), this,   SIGNAL(signalLoadJob()));
    connect(ui->pushButton_Stop,        SIGNAL(clicked(bool)), this,   SIGNAL(signalStopJob()));
    connect(ui->pushButton_Pause,       SIGNAL(clicked(bool)), this,   SIGNAL(signalPauseJob()));
    connect(ui->pushButton_Abort,       SIGNAL(clicked(bool)), this,   SIGNAL(signalAbortJob()));
    connect(ui->pushButton_Exit,        SIGNAL(clicked(bool)), this,   SIGNAL(signalExit()));
}

void ControlBar::setMaximumLayers(int maximum)
{
    ui->spinBox_StopLayer->setMaximum(maximum);
    ui->spinBox_StartLayer->setMaximum(maximum);
}

void ControlBar::setStopLayerValue(int value)
{
    ui->spinBox_StopLayer->setValue(value);
}

void ControlBar::setStartLayerValue(int value)
{
    ui->spinBox_StartLayer->setValue(value);
}

void ControlBar::slotSetJobStatus(const QString &status)
{
    ui->lineEdit_JobStatus->setText(status);
}

void ControlBar::slotSetJobProgressValue(int value)
{
    ui->progressBar_JobProgress->setValue(value);
}

void ControlBar::slotStartJob()
{
    int startLayer = ui->spinBox_StartLayer->value();
    int stopLayer = ui->spinBox_StopLayer->value();

    emit signalStartJob(startLayer,stopLayer);
}

void ControlBar::slotSetProgressStatus(const QString &satatus)
{
    ui->label_ProgressStatus->setText(satatus);
}
