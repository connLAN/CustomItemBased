#ifndef QCUSTOMPLOTEXT_H
#define QCUSTOMPLOTEXT_H

#include <QObject>
#include <QWidget>
#include "qcustomplot.h"

class QCustomPlotExt : public QCustomPlot
{
    Q_OBJECT
public:
    QCustomPlotExt(QWidget* parent);
    virtual ~QCustomPlotExt();

    QCPCurve* addCurve(const QVector<double>& x, const QVector<double>& y, QPair<QPen,QBrush> pb);
    QCPCurve* addCurve(const QVector<QPair<double,double>>& xy,QPair<QPen,QBrush> pb);

    virtual void initialize();
    void setProportion(double ratio);
    void setAutoScale(bool value);
    void rescale();
	void clearData();
    void clear();
    void setGridVisibility(bool visibility);
    void setAxisVisibility(bool visibility);
    void setCoordinatesVisibility(bool visibility);

public slots:
    void slotSetGridVisibility(bool visibility);
    void slotSetAxisVisibility(bool visibility);
    void slotSetCoordinatesVisibility(bool visibility);
private slots:
    void slotXRangeChanged(QCPRange range);
    void slotYRangeChanged(QCPRange range);
    void slotMouseDoubleClick(QMouseEvent*);
    void slotSelectionChanged();
signals:
    void signalSelectionChanged(QList<QCPAbstractPlottable*>);
private:
    bool mIsAutoScale{false};
    bool mIsCoordinates{true};
    double mRatio{1.0};
    void drawCoordinates(QList<QCPAbstractPlottable*> plotables);
    void adjustProportion();
};

#endif // QCUSTOMPLOTEXT_H
