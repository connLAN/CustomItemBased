#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "CustomItem.h"

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
    void slotTimeout();
    void slotCurrentChanged(const CustomItem* item,int row,int column);
    void slotCurrentChanged(CustomItemData data, int row, int column);
signals:
    void signalStatusMonitorUpdate(const QList<CustomItem>& items);
    void signalStatusMonitorUpdate(CustomItem* rootItem);
    void signalBuildListMonitorUpdate(CustomItem* rootItem);
private:
    void initModel();
    Ui::MainWindow *ui;
    QTimer* mTimer;
};

#endif // MAINWINDOW_H
