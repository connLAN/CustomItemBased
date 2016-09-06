#ifndef CUSTOMITEMTREEVIEW_H
#define CUSTOMITEMTREEVIEW_H

#include <QObject>
#include <QTreeView>

#include "CustomItemTreeModel.h"
#include "CustomItemDelegate.h"

class CustomItemTreeView : public QTreeView
{
    Q_OBJECT
public:
    CustomItemTreeView(QWidget *parent = Q_NULLPTR);
    void setHeaders(const QVector<QString>& headers);
    void setItems(CustomItem* rootItem);
    void updateItems(CustomItem* rootItem);
    void resizeViewToContents();
    void setAutoResizeToContents(bool isResize);

public slots:
    void slotCurrentChanged(const QModelIndex& currentIndex,const QModelIndex& previosIndex);
	void slotExpanded(const QModelIndex& currentIndex);

signals:
    void signalCurrentChanged(const CustomItem* item,int row, int column);

private:
    CustomItemTreeModel* mModel;
    CustomItemDelegate* mDelegate;
    QItemSelectionModel* mSelectionModel;
    bool mIsAutoResizeToContents{true};
    void init();
};

#endif // CUSTOMITEMTREEVIEW_H
