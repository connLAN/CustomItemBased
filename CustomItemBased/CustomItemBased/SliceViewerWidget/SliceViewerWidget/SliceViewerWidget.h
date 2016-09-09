#ifndef SLICEVIEWERWIDGET_H
#define SLICEVIEWERWIDGET_H

#include <QWidget>
#include "QCustomPlotExt.h"

namespace Ui {
class SliceViewerWidget;
}

struct SegmentParams{
    QString mType;
    QPair<QPen,QBrush> mPenBrush;
};

class SliceViewerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SliceViewerWidget(QWidget *parent = 0);
    ~SliceViewerWidget();

    void addSegment(const QVector<double>& x, const QVector<double>& y,int id = 0);
    void addSegment(const QVector<QPair<double,double>>& xy,int id = 0);
    void setSegmentParams(const QMap<int,SegmentParams>& segmentsParamsMap);
public slots:
    void slotSegmentFilterChanged(QModelIndex,QModelIndex,QVector<int>);
private:
    Ui::SliceViewerWidget *ui;
    void initialize();
    QMap<int,QVector<QCPCurve*>>    mSegmentsMap;
    QMap<int,SegmentParams>         mSegmentsParamsMap;
    QStandardItemModel*             mComboCheckBoxModel;
    void setSegmentsVisibility(bool visibility);
    void test();
};

#endif // SLICEVIEWERWIDGET_H
