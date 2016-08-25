#ifndef CUSTOMITEMDATA_H
#define CUSTOMITEMDATA_H

#include <QMap>
#include <QString>
#include <QVariant>
#include <QVector>
#include <QList>

class CustomItemData
{
    struct CustomItemProperty
    {
        CustomItemProperty(const QString& name, const QVariant& value)
            :mName(name),mValue(value)
        {}
        CustomItemProperty(){}
        QString     mName;
        QVariant    mValue;
    };
public:
    CustomItemData();
    void addProperty(const QString& propertyName, const QVariant& propertyValue);
    void setProperty(const QString& propertyName, const QVariant& propertyValue);
    QVariant getPropertyValue(const QString& propertyName) const;
    QVariant getPropertyValue(int propertyIndex) const;
    int getPropertiesCount() const;

private:
    QVector<CustomItemProperty> mProperties;
    QMap<QString,int> mIndexes;
    int mPropertiesCount{0};
};

Q_DECLARE_METATYPE(CustomItemData)
Q_DECLARE_METATYPE(CustomItemData*)
#endif //CUSTOMITEM_H
