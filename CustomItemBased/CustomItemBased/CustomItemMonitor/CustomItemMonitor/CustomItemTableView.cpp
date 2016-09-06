#include "CustomItemTableView.h"

CustomItemTableView::CustomItemTableView(QWidget *parent)
    :QTableView(parent)
{
    init();
}

void CustomItemTableView::setHeaders(const QVector<QString> &headers)
{
    mModel->setHeaders(headers);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::setItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::setItems(const QList<CustomItem> &items)
{
    mModel->setItems(items);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::updateItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::updateItems(const QList<CustomItem> &items)
{
    mModel->setItems(items);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTableView::resizeViewToContents()
{
    resizeColumnsToContents();
    resizeRowsToContents();
}

void CustomItemTableView::setAutoResizeToContents(bool isResize)
{
    mIsAutoResizeToContents = isResize;
}

void CustomItemTableView::slotCurrentChanged(QModelIndex currentIndex, QModelIndex previosIndex)
{
    if(!currentIndex.isValid())
        return;

    QVariant var=currentIndex.model()->data(currentIndex);
    CustomItemData itemData=var.value<CustomItemData>();

    emit signalCurrentChanged(itemData, currentIndex.row(), currentIndex.column());
}

void CustomItemTableView::init()
{
    mModel = new CustomItemTableModel(this);
    mDelegate = new CustomItemDelegate(this);
    mSelectionModel = new QItemSelectionModel(mModel,this);

    setModel(mModel);
    setItemDelegate(mDelegate);
    setShowGrid(false);
    setSelectionModel(mSelectionModel);
    resizeViewToContents();

    connect(mSelectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),   this,   SLOT(slotCurrentChanged(QModelIndex,QModelIndex)));
}
