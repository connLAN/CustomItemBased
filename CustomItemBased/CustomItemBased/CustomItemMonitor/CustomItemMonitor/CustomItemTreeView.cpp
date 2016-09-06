#include "CustomItemTreeView.h"

CustomItemTreeView::CustomItemTreeView(QWidget *parent)
    :QTreeView(parent)
{
    init();
}

void CustomItemTreeView::setHeaders(const QVector<QString> &headers)
{
    mModel->setHeaders(headers);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::setItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::updateItems(CustomItem *rootItem)
{
    mModel->setItems(rootItem);
    if(mIsAutoResizeToContents)
        resizeViewToContents();
}

void CustomItemTreeView::resizeViewToContents()
{
    resizeColumnToContents(0);
}

void CustomItemTreeView::setAutoResizeToContents(bool isResize)
{
    mIsAutoResizeToContents = isResize;
}

void CustomItemTreeView::slotCurrentChanged(const QModelIndex& currentIndex,const QModelIndex& previosIndex)
{
    if(!currentIndex.isValid())
        return;

    CustomItem* item = dynamic_cast<const CustomItemTreeModel*>(currentIndex.model())->getItem(currentIndex);
    if(item)
        emit signalCurrentChanged(item, currentIndex.row(), currentIndex.column());
}


void CustomItemTreeView::slotExpanded(const QModelIndex& currentIndex)
{
    if(mIsAutoResizeToContents)
        resizeViewToContents();
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
	connect(this, SIGNAL(expanded(QModelIndex)), this, SLOT(slotExpanded(QModelIndex)));
}
