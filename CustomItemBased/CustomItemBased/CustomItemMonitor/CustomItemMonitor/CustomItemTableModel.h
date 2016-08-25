#ifndef CUSTOMITEMTABLEMODEL_H
#define CUSTOMITEMTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QVector>
#include "CustomItem.h"

class CustomItemTableModel : public QAbstractTableModel
{
public:
    explicit CustomItemTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);

    bool insertRows(int row, int count, const QModelIndex &parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setItems(CustomItem* rootItem);
    void setItems(const QList<CustomItem>& items);
    void setHeaders(const QVector<QString>& headers);

private:
    QList<CustomItem> mItems;
    QVector<QString> mHeaders;
};

#endif // CUSTOMITEMTABLEMODEL_H
