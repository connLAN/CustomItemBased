#ifndef CUSTOMITEMWIDGETS_H
#define CUSTOMITEMWIDGETS_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QSpinBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QLCDNumber>
#include <QProgressBar>

#include "qcustomplot.h"
#include "CustomItemTypes.h"

class QLCDNumberSI : public QLCDNumber
{
public:
    QLCDNumberSI(QWidget* parent = 0);
    void setValue(double value);
    void setSIValue(const QVariant& value);
};

class QProgressBarSI : public QProgressBar
{
public:
    QProgressBarSI(QWidget* parent = 0);
    void setSIValue(const QVariant& value);
};

class QLineEditSI : public QLineEdit
{
public:
    QLineEditSI(QWidget* parent = 0);
    void setValue(const QString& value);
    void setSIValue(const QVariant& value);
};

class QSpinBoxSI : public QSpinBox
{
public:
    QSpinBoxSI(QWidget* parent = 0);
    void setSIValue(const QVariant& value);
};

class QDoubleSpinBoxSI : public QDoubleSpinBox
{
public:
    QDoubleSpinBoxSI(QWidget* parent = 0);
    void setSIValue(const QVariant& value);
};

class QRadioButtonSI : public QRadioButton
{
public:
    QRadioButtonSI(QWidget* parent = 0);
    void setSIValue(const QVariant& value);
};

class QCustomPlotSI : public QCustomPlot
{
public:
    QCustomPlotSI(QWidget* parent = 0);
    virtual void setData(const QVector<double>& xData,const QVector<double>& yData) = 0;
    virtual void setSIValue(const QVariant& value) = 0;
    void setYData(const QVector<double>& yData);
};

class QBarsPlotSI : public QCustomPlotSI
{
public:
    QBarsPlotSI(QWidget* parent = 0);
    void setData(const QVector<double>& xData,const QVector<double>& yData);
    void setSIValue(const QVariant& value);
private:
    QCPBars *mBars;
};

class QGraphPlotSI : public QCustomPlotSI
{
public:
    QGraphPlotSI(QWidget* parent = 0);
    void setData(const QVector<double>& xData,const QVector<double>& yData);
    void setSIValue(const QVariant& value);
private:
    QCPGraph *mGraph;
};
#endif // CUSTOMITEMWIDGETS_H
