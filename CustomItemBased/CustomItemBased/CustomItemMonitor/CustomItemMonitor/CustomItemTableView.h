#ifndef CUSTOMITEMTABLEVIEW_H
#define CUSTOMITEMTABLEVIEW_H

#include <QObject>
#include <QTableView>

#include "CustomItemTableModel.h"
#include "CustomItemDelegate.h"
#include <QItemSelectionModel>

class CustomItemTableView : public QTableView
{
    Q_OBJECT
public:
    CustomItemTableView(QWidget *parent = Q_NULLPTR);
    void setHeaders(const QVector<QString>& headers);
    void setItems(CustomItem* rootItem);
    void setItems(const QList<CustomItem>& items);
    void updateItems(CustomItem* rootItem);
    void updateItems(const QList<CustomItem>& items);
    void resizeViewToContents();

public slots:
    void slotCurrentChanged(QModelIndex currentIndex,QModelIndex previosIndex);

signals:
    void signalCurrentChanged(CustomItemData data,int row, int column);

private:
    CustomItemTableModel* mModel;
    CustomItemDelegate* mDelegate;
    QItemSelectionModel* mSelectionModel;
    void init();
};

#endif // CUSTOMITEMTABLEVIEW_H
