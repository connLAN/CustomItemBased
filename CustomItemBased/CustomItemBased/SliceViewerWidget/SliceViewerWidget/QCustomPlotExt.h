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
    void setAutoScale(bool value);
    void rescale();
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
    void drawCoordinates(QList<QCPAbstractPlottable*> plotables);
};

#endif // QCUSTOMPLOTEXT_H
