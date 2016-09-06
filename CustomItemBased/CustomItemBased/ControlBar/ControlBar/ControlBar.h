#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QWidget>

namespace Ui {
class ControlBar;
}

class ControlBar : public QWidget
{
    Q_OBJECT

public:
    explicit ControlBar(QWidget *parent = 0);
    ~ControlBar();

    void setMaximumLayers(int maximum);
    void setStopLayerValue(int value);
    void setStartLayerValue(int value);

public slots:
    void slotSetJobStatus(const QString& status);
    void slotSetProgressStatus(const QString& status);
    void slotSetJobProgressValue(int value);

signals:
    void signalLoadJob();
    void signalStartJob(int startLayer,int stopLayer);
    void signalPauseJob();
    void signalStopJob();
    void signalAbortJob();
    void signalExit();

private slots:
    void slotStartJob();

private:
    Ui::ControlBar *ui;
    void init();
};

#endif // CONTROLBAR_H
