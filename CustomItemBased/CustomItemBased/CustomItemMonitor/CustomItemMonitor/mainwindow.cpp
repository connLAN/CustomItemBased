#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "CustomItemTableModel.h"
#include "CustomItemDelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mTimer = new QTimer(this);
    connect(mTimer,             SIGNAL(timeout()),   this,   SLOT(slotTimeout()));
    connect(this,               SIGNAL(signalStatusMonitorUpdate(CustomItem*)),                     ui->tableMonitor,       SLOT(slotUpdateItems(CustomItem*)));
    connect(this,               SIGNAL(signalStatusMonitorUpdate(const QList<CustomItem>&)),        ui->tableMonitor,       SLOT(slotUpdateItems(const QList<CustomItem>&)));
    connect(this,               SIGNAL(signalBuildListMonitorUpdate(CustomItem*)),                  ui->treeMonitor,        SLOT(slotUpdateItems(CustomItem*)));
    connect(ui->tableMonitor,   SIGNAL(signalCurrentChanged(CustomItemData,int,int)),               this,                   SLOT(slotCurrentChanged(CustomItemData,int,int)));
    connect(ui->treeMonitor,    SIGNAL(signalCurrentChanged(const CustomItem*,int,int)),            this,                   SLOT(slotCurrentChanged(const CustomItem*,int,int)));
    slotTimeout();
    mTimer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimeout()
{
    static bool stage = true;
    int vecSize = std::rand()/1000;

    std::vector<double> stdVector;
    stdVector.resize(vecSize);
    std::generate_n(stdVector.begin(),vecSize,std::rand);

    int integerValue(std::rand()/100);
    double doubleValue (std::rand()/100.0);
    bool booleanValue (stage);
    QString stringValue;
    stringValue="str:"+QString().number(integerValue);

    SIString si_string(stringValue);
    SIProgress si_progress(integerValue,0,100);
    SILcd si_lcd (std::rand()/300.0,SILcd::HEX);
    SIInteger si_integer(integerValue,0,500);
    SIDouble si_double(doubleValue,10,90);
    SIBoolean si_boolean(booleanValue);
    SIBars si_bars(QVector<double>().fromStdVector(stdVector));
    SIGraph si_graph(QVector<double>().fromStdVector(stdVector));


    CustomItem* rootItem = new CustomItem();

    CustomItem* item = new CustomItem("SIString:",QVariant().fromValue(si_string),"desc1");
    item->addItem( new CustomItem("SIDouble:",QVariant().fromValue(si_double),"desc2"));
    item->addItem( new CustomItem("SIProgress:",QVariant().fromValue(si_progress),"desc3"));

    rootItem->addItem( item );

    rootItem->addItem( new CustomItem("SIString:",QVariant().fromValue(si_string),"desc1"));
    rootItem->addItem( new CustomItem("SIDouble:",QVariant().fromValue(si_double),"desc2"));
    rootItem->addItem( new CustomItem("SIProgress:",QVariant().fromValue(si_progress),"desc3"));
    rootItem->addItem( new CustomItem("SIInteger:",QVariant().fromValue(si_integer),"desc4"));
    rootItem->addItem( new CustomItem("SILCD:",QVariant().fromValue(si_lcd),"desc5"));
    rootItem->addItem( new CustomItem("SIBoolean:",QVariant().fromValue(si_boolean),"desc6"));
    rootItem->addItem( new CustomItem("SIBars:",QVariant().fromValue( si_bars ),"desc7"));
    rootItem->addItem( new CustomItem("SIGraph:",QVariant().fromValue( si_graph ),"desc7"));
    rootItem->addItem( new CustomItem("Integer:",integerValue,"desc8"));
    rootItem->addItem( new CustomItem("Double:",doubleValue,"desc9"));
    rootItem->addItem( new CustomItem("Boolean:",booleanValue,"desc10"));
    rootItem->addItem( new CustomItem("String:",stringValue,"desc11"));

    QList<CustomItem> itemsList;
    itemsList   << CustomItem("SIString:",QVariant().fromValue(si_string),"desc1")
                << CustomItem("SIDouble:",QVariant().fromValue(si_double),"desc2")
                << CustomItem("SIProgress:",QVariant().fromValue(si_progress),"desc3")
                << CustomItem("SIInteger:",QVariant().fromValue(si_integer),"desc4")
                << CustomItem("SILCD:",QVariant().fromValue(si_lcd),"desc5")
                << CustomItem("SIBoolean:",QVariant().fromValue(si_boolean),"desc6")
                << CustomItem("SIBars:",QVariant().fromValue( si_bars ),"desc7")
                << CustomItem("SIGraph:",QVariant().fromValue( si_graph ),"desc7")
                << CustomItem("Integer:",integerValue,"desc8")
                << CustomItem("Double:",doubleValue,"desc9")
                << CustomItem("Boolean:",booleanValue,"desc10")
                << CustomItem("String:",stringValue,"desc11");

    emit signalStatusMonitorUpdate(itemsList);
    emit signalBuildListMonitorUpdate(rootItem);

    stage = !stage;
}

void MainWindow::slotCurrentChanged(const CustomItem* item, int row, int column)
{
    qDebug()<<"row="<<row<<"column="<<column<<"data:"<<item->getData().getPropertyValue("name");
}
void MainWindow::slotCurrentChanged(CustomItemData data, int row, int column)
{
    qDebug()<<"row="<<row<<"column="<<column<<"data:"<<data.getPropertyValue("name");
}
