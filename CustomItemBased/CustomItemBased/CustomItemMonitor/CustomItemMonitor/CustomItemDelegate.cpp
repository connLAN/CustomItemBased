#include "CustomItemDelegate.h"
#include "CustomItemData.h"

CustomItemDelegate::CustomItemDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
    mWidget=new CustomItemWidget();
}

CustomItemDelegate::~CustomItemDelegate()
{
    delete mWidget;
}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    mWidget->setCurrentPropertyIndex( index.column() );
    QVariant var=index.model()->data(index);

    if(var.isValid())
    {
        QString typeName(var.typeName());

        if(typeName == "CustomItemData")
        {
            CustomItemData data=var.value<CustomItemData>();
            mWidget->setStyleOption(option);
            mWidget->setData(data);
            mWidget->setFixedSize(option.rect.width(),option.rect.height());
            QPixmap pixmap(mWidget->size());
            mWidget->render(&pixmap);
            painter->drawPixmap(option.rect,pixmap);
        }
        else
            QStyledItemDelegate::paint(painter,option,index);
    }
}
/*
QSize CustomItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return mWidget->getSize();
}
*/
QWidget *CustomItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    CustomItemWidget* pEditor=new CustomItemWidget(parent);
    connect(pEditor,SIGNAL(signalCommit()),this,SLOT(slotCommit()));
    return pEditor;
}

void CustomItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    CustomItemWidget* pEditor=qobject_cast<CustomItemWidget*>(editor);
    CustomItemData data = index.model()->data(index).value<CustomItemData>();
    pEditor->setCurrentPropertyIndex( index.column() );
    pEditor->setData(data);
}

void CustomItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    CustomItemWidget* pEditor=qobject_cast<CustomItemWidget*>(editor);
    model->setData(index,QVariant().fromValue(pEditor->getData()));
}

void CustomItemDelegate::slotCommit()
{
    CustomItemWidget* pEditor=qobject_cast<CustomItemWidget*>(sender());
    emit commitData(pEditor);
    emit closeEditor(pEditor);
}
