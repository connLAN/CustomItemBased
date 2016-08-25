#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include "CustomItemWidget.h"
#include "CustomItemTypes.h"

class CustomItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CustomItemDelegate(QObject* parent =0);

    ~CustomItemDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

public slots:
    void slotCommit();

private:
    CustomItemWidget* mWidget;
};
#endif // CUSTOMITEMDELEGATE_H
