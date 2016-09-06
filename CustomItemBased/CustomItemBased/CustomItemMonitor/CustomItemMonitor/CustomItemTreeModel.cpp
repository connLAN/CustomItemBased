#include <QtWidgets>
#include "CustomItem.h"
#include "CustomItemTreeModel.h"
#include <QDebug>

CustomItemTreeModel::CustomItemTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = 0;//new CustomItem();
}
CustomItemTreeModel::CustomItemTreeModel(CustomItem *rootItem, QObject *parent)
    : QAbstractItemModel(parent)
{
    mRootItem = rootItem;
}

CustomItemTreeModel::~CustomItemTreeModel()
{
    delete mRootItem;
}

QVariant CustomItemTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    CustomItem *item = getItem(index);

    if(item == 0)
        return QVariant();

    QVariant value = item->getData().getPropertyValue(index.column());
    switch(value.type())
    {
        case QVariant::Type::String :
        case QVariant::Type::Int :
        case QVariant::Type::Double :
            return value;
        break;
        default:
            return QVariant().fromValue(item->getData());
        break;
    }
}

bool CustomItemTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    CustomItem *item = getItem(index);
    if(item == 0)
        return false;

    CustomItemData data = value.value<CustomItemData>();
    item->setData(data);
    emit dataChanged(index, index);

    return true;
}

QVariant CustomItemTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return mHeaders[section];

    return QVariant();
}

bool CustomItemTreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    return false;
}

int CustomItemTreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return mHeaders.size();
}

Qt::ItemFlags CustomItemTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    return flags;
}

CustomItem *CustomItemTreeModel::getItem(const QModelIndex &index) const
{
    if(mRootItem == 0)
        return 0;

    if (!index.isValid())
        return mRootItem;

    CustomItem *item = static_cast<CustomItem*>(index.internalPointer());

    if (item)
        return item;
    else
        return 0;
}

QModelIndex CustomItemTreeModel::index(int row, int column, const QModelIndex &parent) const
{

    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    CustomItem *mParent = getItem(parent);

    if(!mParent)
        return QModelIndex();

    CustomItem *childItem = mParent->getItem(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CustomItemTreeModel::parent(const QModelIndex &index) const
{

    if (!index.isValid())
        return QModelIndex();

    CustomItem *childItem = getItem(index);

    if(childItem == 0)
        return QModelIndex();

    CustomItem *mParent = childItem->getParent();

    if (mParent == mRootItem)
        return QModelIndex();

    return createIndex(mParent->getNumber(), 0, mParent);
}

int CustomItemTreeModel::rowCount(const QModelIndex &parent) const
{
    CustomItem *mParent = getItem(parent);
    if(mParent !=0)
        return mParent->itemsCount();
    else
        return 0;
}

void CustomItemTreeModel::setItems(CustomItem* items)
{
    beginResetModel();
    if(mRootItem != 0 )
        delete mRootItem;
    mRootItem = items;
    endResetModel();
}

void CustomItemTreeModel::setHeaders(const QVector<QString> &headers)
{
    mHeaders = headers;
}

const QVector<QString>& CustomItemTreeModel::getHeaders()
{
	return mHeaders;
}
