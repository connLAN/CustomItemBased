#ifndef YUZZVIEWERWIDGET_H
#define YUZZVIEWERWIDGET_H

#include <QObject>
#include <QWidget>

#include "YuzzViewer.h"
#include "PixmapWidget.h"
#include "structs.h"
#include "CustomItemTreeMonitor.h"

namespace Ui {
class YuzzViewerWidget;
}

class YuzzViewerWidget : public QWidget
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
    QVector<PixmapWidget*>  mPixmapWidgets;
    BANANA_INFO             mBananaGeometry;
    void build();
    void buildPixmapWidgetsFrame(bool isShowAll);
    void update(bool isUpdateAll = false);
    void updateDescription();
    void updatePixmap();
    void updateImage();
    void updateInformation();
    Ui::YuzzViewerWidget *ui;
};

#endif // YUZZVIEWERWIDGET_H
