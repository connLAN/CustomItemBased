#include "CustomItemData.h"

CustomItemData::CustomItemData(){}

void CustomItemData::addProperty(const QString &propertyName, const QVariant &propertyValue)
{
    if(!mIndexes.contains(propertyName))
    {
        mProperties.push_back( CustomItemProperty(propertyName,propertyValue) );
        mIndexes[propertyName] = mPropertiesCount;
        ++mPropertiesCount;
    }
}

void CustomItemData::setProperty(const QString &propertyName, const QVariant &propertyValue)
{
    if(mIndexes.contains(propertyName))
    {
        int index = mIndexes[propertyName];
        mProperties[index].mValue = propertyValue;
    }
}

QVariant CustomItemData::getPropertyValue(const QString &propertyName) const
{
    if(mIndexes.contains(propertyName))
    {
        int index = mIndexes[propertyName];
        return mProperties[index].mValue;
    }
    else
        return QVariant();
}

QVariant CustomItemData::getPropertyValue(int propertyIndex) const
{
    if( (0 <= propertyIndex) && (propertyIndex < mPropertiesCount) )
        return mProperties[propertyIndex].mValue;
    return QVariant();
}

int CustomItemData::getPropertiesCount() const
{
    return mPropertiesCount;
}
