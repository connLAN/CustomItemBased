#ifndef YUZZVIEWERWIDGET_H
#define YUZZVIEWERWIDGET_H

#include <QObject>
#include <QFrame>
#include <QPixmap>
#include <QTabWidget>
#include <QImage>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSlider>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QProgressBar>
#include <QScrollBar>
#include <QPainter>

#include "YuzzViewer.h"
#include "PixmapWidget.h"
#include "structs.h"
#include "CustomItemTreeMonitor.h"

class YuzzViewerWidget : public QFrame
{
    Q_OBJECT
public:
    YuzzViewerWidget(QWidget* parent = Q_NULLPTR);
    ~YuzzViewerWidget();

public slots:
    void slotUpdate(int layer, int stripe, int channel, const QStringList& description, const QPixmap& pixmap);
    void slotUpdate(int layer, int stripe, int channel, const QStringList& description, const QImage& image);
    void slotUpdate();
    void slotShowAllChannels(bool isShowAll);
    void slotShowRotatedPixmap(bool isRotated);
    void slotShowDifferencePixmap(bool isDifferenced);
    void slotShowBananedPixmap(bool isBananed);
    void slotInitialize(int layersNumber,int stripesNumber,int channelsNumber,int startLayer,BANANA_INFO bananaGeometry);
    void slotSetCurrentLayer(int layer);
    void slotSetCurrentStripe(int stripe);
    void slotSetCurrentChannel(int channel);
    void slotSetCurrent(const CustomItem* item,int row,int column);
	void slotFinalize(int layersNumber);
protected:
    void resizeEvent(QResizeEvent *);

private:
    YuzzViewer              mYuzzViewer;
    int                     mCounter{0};
    int                     mMaxCounter{0};
    int                     mPixmapWidgetsNumder{1};
    QTabWidget*             mTabWidget;
    CustomItemTreeMonitor*  mBuildListWidget;
    QTextEdit*              mDescriptionWidget;
    QVector<PixmapWidget*>  mPixmapWidgets;
    QScrollArea*            mScrollArea;
    QFrame*                 mPixmapWidgetsFrame{mPixmapWidgetsFrame};
    QCheckBox*              mIsRotatedPixmap;
    QCheckBox*              mIsShowAllChannels;
    QCheckBox*              mIsShowDifference;
    QProgressBar*           mProgress;
    BANANA_INFO             mBananaGeometry;
    void build();
    void buildPixmapWidgetsFrame(bool isShowAll);
    void update(bool isUpdateAll = false);
    void updateDescription();
    void updatePixmap();
    void updateImage();
    void updateInformation();
};

#endif // YUZZVIEWERWIDGET_H
