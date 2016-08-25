#include "CustomItemTreeView.h"

CustomItemTreeView::CustomItemTreeView(QWidget *parent)
    :QTreeView(parent)
{
    init();
}

void CustomItemTreeView::setHeaders(const QVector<QString> &headers)
{
    mModel->setHeaders(headers);
    resizeViewToContents();
}

void CustomItemTreeView::setItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    resizeViewToContents();
}

void CustomItemTreeView::updateItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    resizeViewToContents();
}

void CustomItemTreeView::resizeViewToContents()
{
    //resizeColumnToContents(0);
    //resizeRowsToContents();
}

void CustomItemTreeView::slotCurrentChanged(QModelIndex currentIndex, QModelIndex previosIndex)
{
    if(!currentIndex.isValid())
        return;

    CustomItem* item = dynamic_cast<const CustomItemTreeModel*>(currentIndex.model())->getItem(currentIndex);
    if(item)
        emit signalCurrentChanged(item, currentIndex.row(), currentIndex.column());
}

void CustomItemTreeView::init()
{
    mModel = new CustomItemTreeModel(this);
    mDelegate = new CustomItemDelegate(this);
    mSelectionModel = new QItemSelectionModel(mModel,this);

    setModel(mModel);
    setItemDelegate(mDelegate);
    setSelectionModel(mSelectionModel);
    resizeViewToContents();

    connect(mSelectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),   this,   SLOT(slotCurrentChanged(QModelIndex,QModelIndex)));
}
