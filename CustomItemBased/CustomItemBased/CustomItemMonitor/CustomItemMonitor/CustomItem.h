#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include "CustomItemData.h"

class CustomItem
{
public:
    CustomItem();
    ~CustomItem();
    explicit CustomItem(const QString& name,const QVariant& value,const QString& description = "");
    explicit CustomItem(CustomItem *parent);
    explicit CustomItem(const CustomItem *item, CustomItem *parent = 0);

    CustomItem& operator=(const CustomItem& item);

    void addProperty(const QString& propertyName, const QVariant& propertyValue);
    void setProperty(const QString& propertyName, const QVariant& propertyValue);
    QVariant getPropertyValue(const QString& propertyName) const;
    QVariant getPropertyValue(int propertyIndex) const;

    const CustomItemData& getData() const;
    void setData(const CustomItemData& data);

    CustomItem *getParent() const;
    void setParent(CustomItem *parent);

    CustomItem *getItem(int getNumber);
    const QList<CustomItem*>& getItems() const;
    void clearItems();

    int getNumber() const;
    CustomItem* addItem(CustomItem* item);
    int itemsCount() const;
    int columnCount() const;

private:
    CustomItemData mData;
    QList<CustomItem*> mItems;
    CustomItem* mParent;

    void clone(const CustomItem   *item);
};

Q_DECLARE_METATYPE(CustomItem)
Q_DECLARE_METATYPE(CustomItem*)

#endif // STATUSINDICATOR_H
