#include "YuzzViewerWidget.h"
#include "ui_YuzzViewerWidget.h"

YuzzViewerWidget::YuzzViewerWidget(QWidget* parent)
    :QWidget(parent),
    ui(new Ui::YuzzViewerWidget)
{
    ui->setupUi(this);

    QGridLayout* layout=    new QGridLayout(ui->mPixmapWidgetsFrame);
    layout->setMargin(0);
    layout->setSpacing(2);
    buildPixmapWidgetsFrame(ui->mIsShowAllChannels->isCheckable());
    ui->mBuildListWidget->setCaptionVisible(false);
    ui->mBuildListWidget->setHeaders(QVector<QString>({"Layers","State"}));

    //signals initialisation
    connect( ui->mIsRotatedPixmap,      SIGNAL(clicked(bool)),                                      this,   SLOT(slotShowRotatedPixmap(bool)) );
    connect( ui->mIsShowAllChannels,    SIGNAL(clicked(bool)),                                      this,   SLOT(slotShowAllChannels(bool)) );
    connect( ui->mTabWidget,            SIGNAL(currentChanged(int)),                                this,   SLOT(slotUpdate()) );
    connect( ui->mBuildListWidget,      SIGNAL(signalCurrentChanged(const CustomItem*,int,int)),    this,   SLOT(slotSetCurrent(const CustomItem*,int,int)));
}

YuzzViewerWidget::~YuzzViewerWidget()
{
    for(auto& w : mPixmapWidgets)
        if(w!=nullptr)
            delete w;
}
void YuzzViewerWidget::buildPixmapWidgetsFrame(bool isShowAll)
{
    for(auto& w : mPixmapWidgets)
        if(w!=nullptr)
            delete w;

    if(isShowAll == true)
        mPixmapWidgets.resize(mPixmapWidgetsNumder);
    else
        mPixmapWidgets.resize(1);

    int colNumber = sqrt(mPixmapWidgets.size());
    int  row(0),col(0);
    for(auto& w : mPixmapWidgets)
    {
        w = new PixmapWidget();
        w->setBananaGeometry(mBananaGeometry);
        QGridLayout* layout = dynamic_cast<QGridLayout*>(ui->mPixmapWidgetsFrame->layout());
        //layout->addWidget(w,row,col);
        layout->addWidget(w,col,row);
        if(col ==  colNumber)
        {
            col = 0;
            ++row;
        }
        else
            col++;
    }
}

void YuzzViewerWidget::build()
{
    /*
//Widgets initialisation
    mTabWidget =            new QTabWidget(this);
    mDescriptionWidget =    new QTextEdit(this);
    mScrollArea =           new QScrollArea(this);
    mPixmapWidgetsFrame=    new QFrame(this);
    QFrame* BuildListFrame=         new QFrame(this);
    mBuildListWidget=       new CustomItemTreeMonitor(this);


    QGridLayout* layout=    new QGridLayout(mPixmapWidgetsFrame);
    layout->setMargin(0);
    layout->setSpacing(2);
    mPixmapWidgetsFrame->setFrameStyle(QFrame::NoFrame);

    mIsRotatedPixmap =      new QCheckBox("Rotated",this);
    mIsRotatedPixmap->setChecked(false);
    mIsShowAllChannels =    new QCheckBox("All channels",this);
    mIsShowAllChannels->setChecked(false);

    mProgress =             new QProgressBar(this);
	mProgress->setAlignment(Qt::AlignHCenter);
	mProgress->setMaximumHeight(16);

    mDescriptionWidget->setReadOnly(true);
    mDescriptionWidget->setFrameStyle(QFrame::NoFrame);

    buildPixmapWidgetsFrame(mIsShowAllChannels->isCheckable());

    mScrollArea->setWidget(mPixmapWidgetsFrame);
    mScrollArea->setFrameStyle(QFrame::NoFrame);
    mScrollArea->setWidgetResizable(true);


    QSizePolicy policy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    policy.setHorizontalStretch(4);
    mTabWidget->setSizePolicy(policy);
    mTabWidget->addTab(mScrollArea,"Pixmap");
    mTabWidget->addTab(mDescriptionWidget,"Description");

    policy.setHorizontalStretch(1);
    BuildListFrame->setSizePolicy(policy);

    mBuildListWidget->setCaptionVisible(false);
    mBuildListWidget->setHeaders(QVector<QString>({"Layers","State"}));

//settingsLayout initialisation
    QHBoxLayout* settingsLayout = new QHBoxLayout();
    settingsLayout->setSpacing(2);
    settingsLayout->setMargin(0);
    //settingsLayout->addStretch();
    settingsLayout->addWidget(mIsRotatedPixmap);
    settingsLayout->addWidget(mIsShowAllChannels);
    settingsLayout->addStretch();

//buildlistLayout initialization
    QVBoxLayout* buildlistLayout = new QVBoxLayout();
    buildlistLayout->setSpacing(2);
    buildlistLayout->setMargin(0);
    buildlistLayout->addWidget(mBuildListWidget);
    buildlistLayout->addLayout(settingsLayout);
	buildlistLayout->addWidget(mProgress);
    BuildListFrame->setLayout(buildlistLayout);

//mainLayout initialization
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainLayout->setSpacing(2);
	mainLayout->setMargin(0);
	mainLayout->addWidget(mTabWidget);
	mainLayout->addWidget(BuildListFrame);

//signals initialisation
    connect( mIsRotatedPixmap,      SIGNAL(clicked(bool)),                                      this,   SLOT(slotShowRotatedPixmap(bool)) );
    //connect( mIsShowDifference,     SIGNAL(clicked(bool)),                                  this,   SLOT(slotShowDifferencePixmap(bool)) );
    connect( mIsShowAllChannels,    SIGNAL(clicked(bool)),                                      this,   SLOT(slotShowAllChannels(bool)) );
    connect( mTabWidget,            SIGNAL(currentChanged(int)),                                this,   SLOT(slotUpdate()) );
    connect( mBuildListWidget,      SIGNAL(signalCurrentChanged(const CustomItem*,int,int)),    this,   SLOT(slotSetCurrent(const CustomItem*,int,int)));
    */
}

void YuzzViewerWidget::slotFinalize(int layersNumber)
{
	mYuzzViewer.setLayersNumber(layersNumber);
	mYuzzViewer.setCurrentLayer(0);
	mYuzzViewer.setCurrentStripe(0);
	mYuzzViewer.setCurrentChannel(0);
    ui->mProgress->setValue(mMaxCounter);
    ui->mBuildListWidget->setHeaders(QVector<QString>({ "Layers" }));
    ui->mBuildListWidget->setItems(mYuzzViewer.getItems());
}
void YuzzViewerWidget::slotUpdate(int layer, int stripe, int channel,const QStringList& description, const QImage& image )
{
    ++mCounter;
    QString information(QString("update #%1 [layer: %2\tstripe:%3\tchannel:%4]").arg(mCounter).arg(layer).arg(stripe).arg(channel));
    //qDebug() << information;
    mYuzzViewer.insert(layer, stripe, channel, YuzzData(image,description,information));

    ui->mProgress->setValue(mCounter);
    ui->mBuildListWidget->setItems(mYuzzViewer.getItems());
    if(mCounter == mMaxCounter)
    {
        mYuzzViewer.setCurrentLayer(0);
        mYuzzViewer.setCurrentStripe(0);
        mYuzzViewer.setCurrentChannel(0);
        
        //update();
    }
    update();
}
void YuzzViewerWidget::slotUpdate(int layer, int stripe, int channel,const QStringList& description, const QPixmap& pixmap )
{
	++mCounter;
    QString information(QString("update #%1 [layer: %2\tstripe:%3\tchannel:%4]").arg(mCounter).arg(layer).arg(stripe).arg(channel));
	//qDebug() << information;
    mYuzzViewer.insert(layer, stripe, channel, YuzzData(pixmap,description,information));
    
    ui->mProgress->setValue(mCounter);
    ui->mBuildListWidget->setItems(mYuzzViewer.getItems());
    if(mCounter == mMaxCounter)
    {
        mYuzzViewer.setCurrentLayer(0);
        mYuzzViewer.setCurrentStripe(0);
        mYuzzViewer.setCurrentChannel(0);
        
		//update();
    }
    update();	
}
void YuzzViewerWidget::slotUpdate()
{
    update(true);
}

void YuzzViewerWidget::slotShowAllChannels(bool isShowAll)
{
    buildPixmapWidgetsFrame(isShowAll);
    slotShowRotatedPixmap( ui->mIsRotatedPixmap->isChecked() );
    update();
}

void YuzzViewerWidget::slotShowRotatedPixmap(bool isRotated)
{
    for(auto w : mPixmapWidgets)
        if(isRotated == true)
            w->rotate(0.0f,0.0f,90.0);
        else
            w->rotate(0.0f,0.0f,0.0f);
    updatePixmap();
    updateImage();
}

void YuzzViewerWidget::slotShowDifferencePixmap(bool isDifferenced)
{
    mYuzzViewer.setDifference( isDifferenced );
    updatePixmap();
    updateImage();
}

void YuzzViewerWidget::slotShowBananedPixmap(bool isBananed)
{
    for(auto w : mPixmapWidgets)
        w->setBananaMode( isBananed );
    updatePixmap();
    updateImage();
}

void YuzzViewerWidget::slotInitialize(int layersNumber, int stripesNumber, int channelsNumber,int startLayer, BANANA_INFO bananaGeometry)
{
    mCounter = 0;
    mBananaGeometry = bananaGeometry;
    mMaxCounter = layersNumber*stripesNumber*channelsNumber;
    mYuzzViewer.initialize( 0, stripesNumber, channelsNumber, startLayer);
    mPixmapWidgetsNumder = channelsNumber;
    for(auto& w : mPixmapWidgets)
        w->setBananaGeometry(bananaGeometry);
    ui->mProgress->setMaximum(mMaxCounter);
    ui->mBuildListWidget->setItems(0);
    ui->mBuildListWidget->setHeaders(QVector<QString>({ "Layers","State" }));
	qDebug() << "slotInitialize";
}
void YuzzViewerWidget::slotSetCurrentLayer(int layer)
{
    mYuzzViewer.setCurrentLayer(layer);
    update();
}
void YuzzViewerWidget::slotSetCurrentStripe(int stripe)
{
    mYuzzViewer.setCurrentStripe(stripe);
    update();
}
void YuzzViewerWidget::slotSetCurrentChannel(int channel)
{
    mYuzzViewer.setCurrentChannel(channel);
    update();
}

void YuzzViewerWidget::slotSetCurrent(const CustomItem* item, int row, int column)
{
	int layer(0);
	static int stripe(0);
	static int channel(0);

    CustomItemData itemData = item->getData();
    QString type = itemData.getPropertyValue("type").toString();
	if (type == "Layer")
	{
		int value = itemData.getPropertyValue("value").toInt();
		layer = item->getData().getPropertyValue("value").toInt();
		mYuzzViewer.setCurrent(layer, stripe, channel);
		update();
	}
	if (type == "Stripe")
	{
		int value = itemData.getPropertyValue("value").toInt();
		CustomItem* layerItem = item->getParent();
		layer = layerItem->getData().getPropertyValue("value").toInt();
		stripe = item->getData().getPropertyValue("value").toInt();
		mYuzzViewer.setCurrent(layer, stripe, channel);
		update();
	}
    if(type == "Channel")
    {
        int value = itemData.getPropertyValue("value").toInt();
        CustomItem* stripeItem = item->getParent();
        CustomItem* layerItem = stripeItem->getParent();
        layer =     layerItem->getData().getPropertyValue("value").toInt();
        stripe =    stripeItem->getData().getPropertyValue("value").toInt();
        channel =   value;
        mYuzzViewer.setCurrent(layer,stripe,channel);
        update();
    }
}




void YuzzViewerWidget::update(bool isUpdateAll)
{
    updateInformation();
    if(isUpdateAll == true)
    {
        updateDescription();
        updatePixmap();
        updateImage();
    }
    else
    {
        if( ui->mTabWidget->currentIndex()== 1)
            updateDescription();
        else
        {
            updatePixmap();
            updateImage();
        }
    }
}

void YuzzViewerWidget::updateDescription()
{
    QStringList description = mYuzzViewer.getCurrentData().getDescription();
    ui->mDescriptionWidget->clear();
    for(const auto& string : description )
        ui->mDescriptionWidget->append(string);
    ui->mDescriptionWidget->verticalScrollBar()->setValue(0);
}

void YuzzViewerWidget::updatePixmap()
{
    int channel(0);
    for(auto w : mPixmapWidgets)
    {
        QPixmap pixmap = mYuzzViewer.getCurrentData(channel).getPixmap();
        if(pixmap.isNull() == true)
            return;
        w->setPixmap(pixmap);
        ++channel;
    }
}
void YuzzViewerWidget::updateImage()
{
    int channel(0);
    int channelCount = mPixmapWidgets.size();
    for(auto w : mPixmapWidgets)
    {
        QImage image;
        if(ui->mIsShowAllChannels->isChecked() == true)
            image = mYuzzViewer.getCurrentData(channelCount - channel - 1).getImage();
        else
            image = mYuzzViewer.getCurrentData(mYuzzViewer.getCurrentChannel()).getImage();
        if(image.isNull() == true)
            return;
        w->setImage(image);
        ++channel;
    }
}
void YuzzViewerWidget::updateInformation()
{
    QString information = mYuzzViewer.getCurrentData().getInformation();

}

void YuzzViewerWidget::resizeEvent(QResizeEvent *)
{
    updatePixmap();
    updateImage();
}
