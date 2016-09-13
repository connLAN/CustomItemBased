#include "SliceViewerWidget.h"
#include "ui_SliceViewerWidget.h"

SliceViewerWidget::SliceViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliceViewerWidget)
{
    ui->setupUi(this);
    initialize();
}

SliceViewerWidget::~SliceViewerWidget()
{
    delete ui;
    if(!mComboCheckBoxModel)
        delete mComboCheckBoxModel;
}

void SliceViewerWidget::clear()
{
	QTime time;
	time = QTime::currentTime();
    ui->mPlot->clear();
	qDebug() << "\tClear plot:" << time.elapsed();

	time = QTime::currentTime();
	mSegmentsMap.clear();
	mSegmentsCountMap.clear();
	qDebug() << "\tClear map:" << time.elapsed();
}

void SliceViewerWidget::clearData()
{
	mSegmentsCountMap.clear();
	ui->mPlot->clearData();
}
void SliceViewerWidget::clearPlotablesData()
{
	for (auto id : mSegmentsMap.keys())
	{
		int segCountPerId = mSegmentsCountMap[id];
		int needToClearData = mSegmentsMap[id].size() - segCountPerId;
		qDebug() << "Delete:" << needToClearData;
		QVector<QCPCurve*>::iterator it;
		for (it = mSegmentsMap[id].begin() + segCountPerId; it < mSegmentsMap[id].end(); ++it)
			(*it)->clearData();
	}
}
void SliceViewerWidget::replot()
{
	//clearPlotablesData();
    ui->mPlot->replot();
}

void SliceViewerWidget::rescale()
{
    ui->mPlot->rescale();
}

void SliceViewerWidget::addSegment(const QVector<double> &x, const QVector<double> &y, int id)
{
    QCPCurve* pCurve;
    //QPair<QPen, QBrush>pb( QPen(QColor(Qt::black)), QBrush(QColor(Qt::transparent)) );
    QPair<QPen, QBrush>pb(QPen(QColor(0,0,0)), QBrush(QColor(0,0,0,0)));
    if(mSegmentsParamsMap.contains(id))
        pb = mSegmentsParamsMap[id].mPenBrush;    
	
	int segCountPerId = ++mSegmentsCountMap[id];

	if (segCountPerId > mSegmentsMap[id].size())
	{
		pCurve = ui->mPlot->addCurve(x, y, pb);
		mSegmentsMap[id].push_back(pCurve);
	}
	else
	{
		pCurve = mSegmentsMap[id][segCountPerId-1];
		pCurve->setData(x, y);
	}

}

void SliceViewerWidget::addSegment(const QVector<QPair<double, double> > &xy, int id)
{
    QVector<double> x,y;
    for(auto point : xy)
    {
        x.push_back(point.first);
        y.push_back(point.second);
    }
    addSegment(x,y,id);
}

void SliceViewerWidget::setSegmentParams(const QMap<int,SegmentParams>& segmentsParamsMap)
{
    mSegmentsParamsMap = segmentsParamsMap;

    if(!mComboCheckBoxModel)
        delete mComboCheckBoxModel;

    mComboCheckBoxModel = new QStandardItemModel(mSegmentsParamsMap.size(), 1);
    int i(0);
    for(auto& param : segmentsParamsMap)
    {
        QStandardItem* item = new QStandardItem(param.mType);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Checked, Qt::CheckStateRole);
        mComboCheckBoxModel->setItem(i++, 0, item);
    }
    connect(mComboCheckBoxModel,  SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),this,       SLOT(slotSegmentFilterChanged(QModelIndex,QModelIndex,QVector<int>)));
    ui->mSegmensFilter->setModel(mComboCheckBoxModel);
    ui->mSegmensFilter->setCurrentText("Segments");
}

void SliceViewerWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QSize s = size();
    int h = s.height()-ui->mSettingsFrame->size().height();
    int w = s.width();
    //int minSize = (h>w)?w:h;
    //s.setHeight(minSize);
    //s.setWidth(minSize);
    //ui->mPlot->setMaximumSize(s);
    //ui->mPlot->updateGeometry();

    ui->mPlot->setProportion((double)w/h);
    ui->mPlot->rescale();
    ui->mPlot->replot();
    qDebug()<<"resize"<<w<<h;
}

void SliceViewerWidget::refilter()
{
    setSegmentsVisibility(true);
    for (int item = 0; item < ui->mSegmensFilter->count(); item++)
    {
        int selectedId = mSegmentsParamsMap.keys().at(item);
        bool visibility = ui->mSegmensFilter->itemData(item, Qt::CheckStateRole).toBool();
        if (mSegmentsMap.contains(selectedId))
            for (auto pSegment : mSegmentsMap[selectedId])
				pSegment->setVisible(visibility);
	}
}


void SliceViewerWidget::slotSegmentFilterChanged(QModelIndex,QModelIndex,QVector<int>)
{
	refilter();
    ui->mPlot->replot();
}

void SliceViewerWidget::initialize()
{
    ui->mPlot->initialize();
    ui->mPlot->setProportion(2.0);
    //QSizePolicy qsp(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //qsp.setHeightForWidth(true);
    //qsp.setWidthForHeight(true);
    //ui->mPlot->setSizePolicy(qsp);
    connect(ui->mIsGrid,        SIGNAL(clicked(bool)),              ui->mPlot,  SLOT(slotSetGridVisibility(bool)));
    connect(ui->mIsAxis,        SIGNAL(clicked(bool)),              ui->mPlot,  SLOT(slotSetAxisVisibility(bool)));
    connect(ui->mIsCoordinates, SIGNAL(clicked(bool)),              ui->mPlot,  SLOT(slotSetCoordinatesVisibility(bool)));
}

void SliceViewerWidget::setSegmentsVisibility(bool visibility)
{
    for(auto& segVector : mSegmentsMap)
		for (auto pSegment : segVector)
			pSegment->setVisible(visibility);
}

void SliceViewerWidget::test()
{
    int id(0);

    QMap<int,SegmentParams> params;
    params.insert(id++,{ "blue",    {QPen(QColor(Qt::blue)),    QBrush(QColor(Qt::transparent))} }) ;
    params.insert(id++,{ "red",     {QPen(QColor(Qt::red)),     QBrush(QColor(Qt::transparent))} }) ;
    params.insert(id++,{ "green",   {QPen(QColor(Qt::green)),   QBrush(QColor(Qt::transparent))} }) ;
    params.insert(id++,{ "yellow",  {QPen(QColor(Qt::yellow)),  QBrush(QColor(Qt::transparent))} }) ;
    setSegmentParams(params);

    clearData();

    id=0;
    addSegment({1,3,8,1},{1,4,7,1},id++);
    addSegment({1,4,7,1},{1,3,8,1},id++);
    addSegment({{1,4},{2,6},{5,3},{1,4}},id++);
    rescale();
    replot();
}
