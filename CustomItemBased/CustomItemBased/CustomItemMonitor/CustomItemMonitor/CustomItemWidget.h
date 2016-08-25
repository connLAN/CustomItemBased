#ifndef CUSTOMITEMWIDGET_H
#define CUSTOMITEMWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>

#include "CustomItemData.h"
#include "CustomItemWidgets.h"
#include "CustomItemTypes.h"

class CustomItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomItemWidget(QWidget *parent = 0);
    explicit CustomItemWidget(CustomItemData data,QWidget *parent = 0);

    void setStyleOption(const QStyleOptionViewItem &option);
    void setData(CustomItemData data);
    CustomItemData getData() const;
    void setCurrentPropertyIndex(int propertyIndex);
    QSize getSize();

signals:
    void signalCommit();

public slots:

private:
    CustomItemData mData;
    int mCurrentPropertyIndex;

    void build();

    void init();

    QVector<QWidget*> mWidgets;
    QWidget* mCurrentWidget;

    QLineEditSI*         mStringWidget;
    QSpinBoxSI*          mIntWidget;
    QDoubleSpinBoxSI*    mDoubleWidget;
    QRadioButtonSI*      mBooleanWidget;
    QBarsPlotSI*         mBarWidget;
    QGraphPlotSI*        mGraphWidget;
    QProgressBarSI*      mProgressWidget;
    QLCDNumberSI*        mLCDWidget;

    QVBoxLayout* mLayout;
    QStyleOptionViewItem mOption;
};

#endif // CUSTOMITEMWIDGET_H
