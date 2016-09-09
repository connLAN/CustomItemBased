#include "QCustomPlotExt.h"

QCustomPlotExt::QCustomPlotExt(QWidget* parent)
    :QCustomPlot(parent)
{
}

QCustomPlotExt::~QCustomPlotExt()
{
    clearPlottables();
    clearItems();
}

void QCustomPlotExt::initialize()
{
    yAxis2->setVisible(true);
    xAxis2->setVisible(true);
    //xAxis->setLabel(tr("mm"));
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//| QCP::iSelectAxes | QCP::iSelectLegend );

    connect(xAxis,  SIGNAL(rangeChanged(QCPRange)),         this,   SLOT(slotXRangeChanged(QCPRange)));
    connect(yAxis,  SIGNAL(rangeChanged(QCPRange)),         this,   SLOT(slotYRangeChanged(QCPRange)));
    connect(this,   SIGNAL(mouseDoubleClick(QMouseEvent*)), this,   SLOT(slotMouseDoubleClick(QMouseEvent*)));
    connect(this,   SIGNAL(selectionChangedByUser()),       this,   SLOT(slotSelectionChanged()));
}

QCPCurve* QCustomPlotExt::addCurve(const QVector<double>& x, const QVector<double>& y, QPair<QPen,QBrush> pb)
{
    QCPCurve* pCurve = new QCPCurve(xAxis,yAxis);
    pCurve->setData(x,y);
    pCurve->setPen(pb.first);
    pCurve->setBrush(pb.second);
    addPlottable(pCurve);
    if(mIsAutoScale)
        rescaleAxes(true);
    return pCurve;
}

QCPCurve* QCustomPlotExt::addCurve(const QVector< QPair<double,double> >& xy, QPair<QPen,QBrush> pb)
{
    QVector<double> x,y;
    for(auto point : xy)
    {
        x.push_back(point.first);
        y.push_back(point.second);
    }

    return addCurve(x,y,pb);
}

void QCustomPlotExt::setAutoScale(bool value)
{
    mIsAutoScale = value;
}

void QCustomPlotExt::rescale()
{
    rescaleAxes(true);
}

void QCustomPlotExt::clear()
{
    clearPlottables();
    clearItems();
}

void QCustomPlotExt::setGridVisibility(bool visibility)
{
    xAxis->grid()->setVisible(visibility);
    yAxis->grid()->setVisible(visibility);
}

void QCustomPlotExt::setAxisVisibility(bool visibility)
{
    QVector<QCPAxis*> axises({xAxis,yAxis,xAxis2,yAxis2});
    for(auto axis : axises)
    {
        axis->setTickLabels(visibility);
        axis->setTicks(visibility);
    }
}

void QCustomPlotExt::setCoordinatesVisibility(bool visibility)
{
    mIsCoordinates = visibility;
}
void QCustomPlotExt::slotSelectionChanged()
{
    const QList<QCPAbstractPlottable*>& plotables = selectedPlottables();
    emit signalSelectionChanged( plotables );
    if(mIsCoordinates)
        drawCoordinates(plotables);
}

void QCustomPlotExt::drawCoordinates(QList<QCPAbstractPlottable*> plotables)
{
    clearItems();
    for(auto plotable : plotables)
    {
        QCPCurve* pCurve = dynamic_cast<QCPCurve*>(plotable);
        QCPCurveDataMap* dataMap = pCurve->data();
        int n(0);
        for(const QCPCurveData& data:*dataMap)
        {
            int x = data.key;
            int y = data.value;
            QCPItemText* point = new QCPItemText(this);
            point->position->setType(QCPItemPosition::ptPlotCoords);
            point->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
            point->position->setCoords(x,y);
            point->setText(QString("#%1\nX:%2\nY:%3").arg(n).arg(x).arg(y));
            point->setTextAlignment(Qt::AlignLeft);
            point->setFont(QFont(font().family(), 8));
            point->setPadding(QMargins(2, 2, 2, 2));
            addItem(point);
            n++;
        }
		break;///Show only one 
    }
}
void QCustomPlotExt::slotXRangeChanged(QCPRange range)
{
    xAxis2->setRange(range);
}
void QCustomPlotExt::slotYRangeChanged(QCPRange range)
{
    yAxis2->setRange(range);
}

void QCustomPlotExt::slotSetGridVisibility(bool visibility)
{
    setGridVisibility(visibility);
    replot();
}

void QCustomPlotExt::slotSetAxisVisibility(bool visibility)
{
    setAxisVisibility(visibility);
    replot();
}

void QCustomPlotExt::slotSetCoordinatesVisibility(bool visibility)
{
    setCoordinatesVisibility(visibility);
    clearItems();
    replot();
}

void QCustomPlotExt::slotMouseDoubleClick(QMouseEvent *)
{
    rescaleAxes(true);
    replot();
}
