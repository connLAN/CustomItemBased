#include "CustomItem.h"
#include <QDebug>

CustomItem::CustomItem()
{
}

CustomItem::~CustomItem()
{
    qDeleteAll(mItems);
}

CustomItem::CustomItem(const QString &name, const QVariant &value, const QString &description)
{
    addProperty("name",name);
    addProperty("value",value);
    addProperty("description",description);
}

CustomItem::CustomItem(CustomItem *parent)
{
    mParent = parent;
}

CustomItem::CustomItem(const CustomItem *item, CustomItem *parent)
{
    mParent = parent;
    clone(item);
}

CustomItem &CustomItem::operator=(const CustomItem &item)
{
    clone(&item);
    return *this;
}

void CustomItem::addProperty(const QString &propertyName, const QVariant &propertyValue)
{
    mData.addProperty(propertyName,propertyValue);
}

void CustomItem::setProperty(const QString &propertyName, const QVariant &propertyValue)
{
    mData.setProperty(propertyName,propertyValue);
}

QVariant CustomItem::getPropertyValue(const QString &propertyName) const
{
    return mData.getPropertyValue(propertyName);
}

QVariant CustomItem::getPropertyValue(int propertyIndex) const
{
    return mData.getPropertyValue(propertyIndex);
}

const CustomItemData &CustomItem::getData() const
{
    return mData;
}

void CustomItem::setData(const CustomItemData &data)
{
    mData = data;
}

CustomItem *CustomItem::getParent() const
{
    return mParent;
}

void CustomItem::setParent(CustomItem *parent)
{
    mParent = parent;
}

CustomItem *CustomItem::getItem(int getNumber)
{
    return mItems.value(getNumber);
}

const QList<CustomItem *> &CustomItem::getItems() const
{
    return mItems;
}

void CustomItem::clearItems()
{
    mItems.clear();
}

int CustomItem::getNumber() const
{
    if (mParent)
        return mParent->mItems.indexOf(const_cast<CustomItem*>(this));

    return 0;
}

CustomItem* CustomItem::addItem(CustomItem *item)
{
    item->setParent(this);
    mItems.append(item);
    return item;
}

int CustomItem::itemsCount() const
{
    return mItems.count();
}

int CustomItem::columnCount() const
{
    return mData.getPropertiesCount();
}

void CustomItem::clone(const CustomItem *item)
{
    mData = item->mData;
    for(auto& it : item->mItems)
    {
        CustomItem* subItem = new CustomItem(it,this);
        mItems.append(subItem);
    }
}
