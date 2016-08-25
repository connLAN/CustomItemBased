#ifndef CUSTOMITEMTABLEMONITOR_H
#define CUSTOMITEMTABLEMONITOR_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QString>
#include <QVector>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QList>

#include "CustomItemTableView.h"

class CustomItemTableMonitor : public QFrame
{
    Q_OBJECT
public:
    CustomItemTableMonitor(QWidget* parent = 0);
    void updateItems(CustomItem* rootItem);
    void updateItems(const QList<CustomItem>& items);
    void setItems(CustomItem* rootItem);
    void setItems(const QList<CustomItem>& items);
    void setHeaders(const QVector<QString>& headers);

public slots:
    void slotUpdateItems(CustomItem* rootItem);
    void slotUpdateItems(const QList<CustomItem>& items);
    void slotSetItems(CustomItem* rootItem);
    void slotSetItems(const QList<CustomItem>& items);
    void slotSetHeaders(const QVector<QString>& headers);
    void slotResizeViewToContents();

signals:
    void signalCurrentChanged(CustomItemData data,int row, int column);

private:
    CustomItemTableView* mView;
    QRadioButton* mCaption;
    QVBoxLayout* mLayout;    

    void build();
    void init();
};

#endif // CUSTOMITEMTABLEMONITOR_H
