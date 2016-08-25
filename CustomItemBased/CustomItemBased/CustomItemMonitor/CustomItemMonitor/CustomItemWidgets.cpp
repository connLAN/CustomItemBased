#include "CustomItemWidgets.h"

//SILCDNumber
QLCDNumberSI::QLCDNumberSI(QWidget *parent)
    :QLCDNumber(parent)
{
    setFrameShape(QLCDNumber::NoFrame);
    setSegmentStyle(QLCDNumber::Flat);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

void QLCDNumberSI::setValue(double value)
{
    display(value);
}

void QLCDNumberSI::setSIValue(const QVariant &value)
{
    SILcd data = value.value<SILcd>();
    setMode(static_cast<QLCDNumber::Mode>( data.getDisplayMode()));
    setValue( data.getValue() );
}

//SIProgressBar
QProgressBarSI::QProgressBarSI(QWidget *parent)
    :QProgressBar(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    setAlignment(Qt::AlignHCenter);
}

void QProgressBarSI::setSIValue(const QVariant &value)
{
    SIProgress data = value.value<SIProgress>();
    auto val = data.getValue();
    auto min = data.getMinimum();
    auto max = data.getMaximum();
    if( val > max ) val = max;
    if( val < min ) val = min;

    setMinimum(min);
    setMaximum(max);
    setValue(val);
}

//SILineEdit
QLineEditSI::QLineEditSI(QWidget *parent)
    :QLineEdit(parent)
{
    setFrame(false);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

void QLineEditSI::setValue(const QString &value)
{
    setText(value);
}

void QLineEditSI::setSIValue(const QVariant &value)
{
    SIString data = value.value<SIString>();
    setText( data.getValue() );
}

//SISpinBox
QSpinBoxSI::QSpinBoxSI(QWidget *parent)
    :QSpinBox(parent)
{
    setFrame(false);
    setButtonSymbols(QSpinBox::NoButtons);
    setMaximum(std::numeric_limits<int>::max());
    setMinimum(std::numeric_limits<int>::min());
    setSpecialValueText(locale().toString(std::numeric_limits<int>::quiet_NaN()));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

void QSpinBoxSI::setSIValue(const QVariant &value)
{
    SIInteger data = value.value<SIInteger>();
    auto val = data.getValue();
    auto min = data.getMinimum();
    auto max = data.getMaximum();
    if( val > max ) val = max;
    if( val < min ) val = min;

    setMinimum(min);
    setMaximum(max);
    setValue(val);
    specialValueText();
}

//SIDoubleSpinBox
QDoubleSpinBoxSI::QDoubleSpinBoxSI(QWidget *parent)
    :QDoubleSpinBox(parent)
{
    setFrame(false);
    setButtonSymbols(QSpinBox::NoButtons);
    setMaximum(std::numeric_limits<double>::max());
    setMinimum(std::numeric_limits<double>::min());
    setSpecialValueText(locale().toString(std::numeric_limits<double>::quiet_NaN()));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

void QDoubleSpinBoxSI::setSIValue(const QVariant &value)
{
    SIDouble data = value.value<SIDouble>();
    auto val = data.getValue();
    auto min = data.getMinimum();
    auto max = data.getMaximum();
    if( val > max ) val = max;
    if( val < min ) val = min;

    setMinimum(min);
    setMaximum(max);
    setValue(val);
    specialValueText();
}

//SIRadioButton
QRadioButtonSI::QRadioButtonSI(QWidget *parent)
    :QRadioButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

void QRadioButtonSI::setSIValue(const QVariant &value)
{
    SIBoolean data = value.value<SIBoolean>();
    setChecked( data.getValue() );
}

//SICustomPlot
QCustomPlotSI::QCustomPlotSI(QWidget *parent)
    :QCustomPlot(parent)
{
    xAxis->setTicks(false);
    yAxis->setTicks(false);
    axisRect()->setupFullAxesBox();
    axisRect()->setAutoMargins(QCP::msNone);
    axisRect()->setMargins(QMargins(1,1,1,1));
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

void QCustomPlotSI::setYData(const QVector<double> &yData)
{
    QVector<double> xData(yData.size());
    for(int i = 0;i<xData.size();i++)
        xData[i]=i;
    setData(xData, yData);
}

//SIBarsPlot
QBarsPlotSI::QBarsPlotSI(QWidget *parent)
    :QCustomPlotSI(parent)
{
    mBars = new QCPBars(xAxis, yAxis);
    addPlottable(mBars);
    mBars->rescaleAxes(true);
    mBars->setWidth(1);
    mBars->setPen(Qt::NoPen);
    mBars->setBrush(QColor(0x99, 0x99, 0x99, 160));
}

void QBarsPlotSI::setData(const QVector<double> &xData, const QVector<double> &yData)
{
    mBars->setData(xData,yData);
    mBars->rescaleValueAxis(true);
    xAxis->setRange(0,xData.size());
}

void QBarsPlotSI::setSIValue(const QVariant &value)
{
    SIBars data = value.value<SIBars>();
    setYData(data.getValue());
}

//SIGraphPlot
QGraphPlotSI::QGraphPlotSI(QWidget *parent)
    :QCustomPlotSI(parent)
{
    mGraph = addGraph(xAxis, yAxis);
    mGraph->rescaleAxes(true);
    mGraph->setPen(QPen( QColor(0x66, 0x66, 0x66) ));
}

void QGraphPlotSI::setData(const QVector<double> &xData, const QVector<double> &yData)
{
    mGraph->setData(xData,yData);
    mGraph->rescaleValueAxis(true);
    xAxis->setRange(0,xData.size());
}

void QGraphPlotSI::setSIValue(const QVariant &value)
{
    SIGraph data = value.value<SIGraph>();
    setYData(data.getValue());
}
