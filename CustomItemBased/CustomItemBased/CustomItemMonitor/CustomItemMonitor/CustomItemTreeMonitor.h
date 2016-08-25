#ifndef CUSTOMITEMTREEMONITOR_H
#define CUSTOMITEMTREEMONITOR_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QString>
#include <QVector>
#include <QTableView>
#include <QTreeView>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHeaderView>

#include "CustomItemTreeView.h"

class CustomItemTreeMonitor : public QFrame
{
    Q_OBJECT
public:
    CustomItemTreeMonitor(QWidget* parent = 0);
    void updateItems(CustomItem* rootItem);
    void setItems(CustomItem* rootItem);
    void setHeaders(const QVector<QString>& headers);
    void setCaption(const QString& text);
    void setCaptionVisible(bool isVisible);
public slots:
    void slotUpdateItems(CustomItem* rootItem);
    void slotSetItems(CustomItem* rootItem);
    void slotSetHeaders(const QVector<QString>& headers);
    void slotResizeViewToContents();

signals:
    void signalCurrentChanged(const CustomItem* item,int row, int column);

private:
    CustomItemTreeView* mView;
    QRadioButton* mCaption;
    QVBoxLayout* mLayout;

    void build();
    void init();
};

#endif // CUSTOMITEMTREEMONITOR_H
