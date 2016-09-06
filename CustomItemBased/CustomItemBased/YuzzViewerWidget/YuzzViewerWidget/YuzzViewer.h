#ifndef YUZZVIEWER_H
#define YUZZVIEWER_H

#include <QVector>
#include <QPixmap>
#include <QStringList>
#include <QString>
#include <QDebug>
#include <QImage>
#include <QPainter>

#include "CustomItem.h"

class YuzzData{
public:
    YuzzData(){
    }
    YuzzData( const QPixmap& pixmap, const QStringList& description, const QString& information )
        :mImage(QImage()), mPixmap(pixmap),mDescription(description),mInformation(information)
    {
    }
    YuzzData( const QImage& image, const QStringList& description, const QString& information )
        :mImage(image),mPixmap(QPixmap()),mDescription(description),mInformation(information)
    {
    }
    ~YuzzData(){}

    const QImage& getImage()const               { return mImage; }
    const QPixmap& getPixmap()const             { return mPixmap; }
    const QStringList& getDescription()const    { return mDescription; }
    const QString& getInformation()const        { return mInformation; }

    void setImage(const QImage& image)                      { mImage = image; }
    void setPixmap(const QPixmap& pixmap)                   { mPixmap = pixmap; }
    void setDescription(const QStringList& description)     { mDescription = description; }
    void setInformation(const QString& information)         { mInformation = information; }

private:
    QImage      mImage;
    QPixmap     mPixmap;
    QStringList mDescription;
    QString     mInformation;
};

class YuzzViewer{
public:
    YuzzViewer();
    ~YuzzViewer();
    inline int getCurrentLayer()const   { return mLayer; }
    inline int getCurrentStripe()const  { return mStripe; }
    inline int getCurrentChannel()const { return mChannel; }
	inline void setLayersNumber(int layersNumber)
	{
		mLayersNumber = layersNumber;
		if (mLayer > mLayersNumber-1)
			mLayer = mLayersNumber-1;
	}
    inline void setCurrentLayer(int layer)
    {
        if(layer<mLayersNumber)
            mLayer = layer;
    }
    inline void setCurrentStripe(int stripe)
    {
        if(stripe<mStripesNumber)
            mStripe = stripe;
    }
    inline void setCurrentChannel(int channel)
    {
        if(channel<mChannelsNumber)
            mChannel = channel;
    }
    inline void setCurrent(int layer,int stripe,int channel)
    {
        setCurrentLayer(layer);
        setCurrentStripe(stripe);
        setCurrentChannel(channel);
    }

    inline void setDifference(bool value)
    {
        mIsDifferensed = value;
    }

    const YuzzData& getCurrentData();
    const YuzzData& getCurrentData(int channel);
    void initialize(int layersNumber,int stripesNumber,int channelsNumber,int startLayer);
    void insert(int layer,int stripe,int channel,const YuzzData& data);
    CustomItem* getItems();

private:
    int mLayer{0};
    int mStripe{0};
    int mChannel{0};
    int mLayersNumber{0};
    int mStripesNumber{0};
    int mChannelsNumber{0};
    bool mIsDifferensed{false};
    QVector< QVector< QVector <YuzzData>>> mOriginalData;
    QVector< QVector< QVector <YuzzData>>> mProcessedData;
    YuzzData blankData;
	int mStartLayer{0};

    void differenceYuzzes(int layer,int stripe);
};

#endif // YUZZVIEWER_H
