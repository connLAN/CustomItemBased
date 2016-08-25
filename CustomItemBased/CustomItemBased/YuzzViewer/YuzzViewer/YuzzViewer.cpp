#include "YuzzViewer.h"
#include "CustomItemTypes.h"
YuzzViewer::YuzzViewer()
{
}

YuzzViewer::~YuzzViewer()
{
}

const YuzzData& YuzzViewer::getCurrentData()
{
    if( (mLayersNumber > 0) && (mStripesNumber > 0) && (mChannelsNumber > 0) )
        if(mIsDifferensed == true)
                return mProcessedData[mLayer][mStripe][mChannel];
            else
                return mOriginalData[mLayer][mStripe][mChannel];
    else
        return blankData;
}
const YuzzData& YuzzViewer::getCurrentData(int channel)
{
    if( (mLayersNumber > 0) && (mStripesNumber > 0) && (mChannelsNumber > 0) && (channel < mChannelsNumber) )
        if(mIsDifferensed == true)
                return mProcessedData[mLayer][mStripe][channel];
            else
                return mOriginalData[mLayer][mStripe][channel];
    else
        return blankData;
}
void YuzzViewer::initialize(int layersNumber, int stripesNumber, int channelsNumber)
{
    mLayersNumber = layersNumber;
    mStripesNumber = stripesNumber;
    mChannelsNumber = channelsNumber;

    mOriginalData.resize(layersNumber);
    for( auto& vStripes : mOriginalData)
    {
        vStripes.resize(stripesNumber);
        for( auto& vChannels : vStripes)
            vChannels.resize(channelsNumber);
    }

    mProcessedData = mOriginalData;
}

void YuzzViewer::insert(int layer, int stripe, int channel, const YuzzData &data)
{
    if( (layer<mLayersNumber) && (stripe<mStripesNumber) && (channel<mChannelsNumber) )
    {
        mOriginalData[layer][stripe][channel]=data;
        mLayer=layer;
        mStripe=stripe;
        mChannel=channel;
        //if(mChannel == mChannelsNumber-1)
            //differenceYuzzes(layer,stripe);
    }
}
void YuzzViewer::differenceYuzzes(int layer, int stripe)
{
    if(layer>0)
    {
        for(int channel = 0; channel < mChannelsNumber; ++channel)
        {
            QImage currentImage = mOriginalData[layer][stripe][channel].getImage();
            QImage previosImage = mOriginalData[layer-1][stripe][channel].getImage();

            int h=qMax(currentImage.size().height(),previosImage.size().height());
            int w=qMax(currentImage.size().width(),previosImage.size().width());

            for(int x = 0; x < w; x++)
                for(int y = 0; y < h; y++)
                {
                    QRgb currentPixel=currentImage.pixel(x,y);
                    QRgb previosPixel=previosImage.pixel(x,y);

                     if(currentPixel==previosPixel)
                     {
                         if(currentPixel!=qRgb(255,255,255))
                            currentImage.setPixel(x,y,qRgb(255,255,255));
                     }
                     else
                         currentImage.setPixel(x,y,qRgb(0,0,0));
                }
            mProcessedData[layer][stripe][channel].setImage(currentImage);
            mProcessedData[layer][stripe][channel].setDescription( mOriginalData[layer][stripe][channel].getDescription() );
            mProcessedData[layer][stripe][channel].setInformation( mOriginalData[layer][stripe][channel].getInformation() );
        }
    }
}
#if(0)
CustomItem *YuzzViewer::getItems()
{
    CustomItem* rootItem = new CustomItem();
    for(int layer=0; layer<mLayersNumber; layer++)
    {
        CustomItem* itemL = new CustomItem("Layer",QVariant().fromValue(SIInteger(layer)));
        rootItem->addItem(itemL);
        for(int stripe=0; stripe<mStripesNumber; stripe++)
        {
            CustomItem* itemS = new CustomItem("Stripe",QVariant().fromValue(SIInteger(stripe)));
            itemL->addItem(itemS);
            for(int chan=0; chan<mChannelsNumber; chan++)
            {
                CustomItem* itemC = new CustomItem("Channel",QVariant().fromValue(SIInteger(chan)));
                itemS->addItem(itemC);
            }
        }
    }
    return rootItem;
}
#else
CustomItem *YuzzViewer::getItems()
{
    CustomItem* rootItem = new CustomItem();
    for(int layer=0; layer<mLayersNumber; layer++)
    {
        CustomItem* itemL = new CustomItem();
        itemL->addProperty("name",QString("Layer %1").arg(layer));
        itemL->addProperty("value",layer);
        itemL->addProperty("type",QString("Layer"));
        rootItem->addItem(itemL);
        for(int stripe=0; stripe<mStripesNumber; stripe++)
        {
            CustomItem* itemS = new CustomItem();
            itemS->addProperty("name",QString("Stripe %1").arg(stripe));
            itemS->addProperty("value",stripe);
            itemS->addProperty("type",QString("Stripe"));

            itemL->addItem(itemS);
            for(int chan=0; chan<mChannelsNumber; chan++)
            {
                CustomItem* itemC = new CustomItem();
                itemC->addProperty("name",QString("Channel %1").arg(chan));
                itemC->addProperty("value",chan);
                itemC->addProperty("type",QString("Channel"));

                itemS->addItem(itemC);
            }
        }
    }
    return rootItem;
}
#endif
/*
void YuzzViewer::differenceYuzzes(int layer, int stripe)
{
    if(layer>0)
    {
        for(int channel = 0; channel < mChannelsNumber; ++channel)
        {
            const QPixmap& currentPixmap = mOriginalData[layer][stripe][channel].getPixmap();
            const QPixmap& previosPixmap = mOriginalData[layer-1][stripe][channel].getPixmap();

            QPainter painter;
            int h=qMax(currentPixmap.rect().height(),previosPixmap.rect().height());
            int w=qMax(currentPixmap.rect().width(),previosPixmap.rect().width());

            QImage currentImage(w,h,QImage::Format_RGB16);
            QImage previosImage(w,h,QImage::Format_RGB16);

            painter.begin(&currentImage);
            painter.drawPixmap(0,0,currentPixmap);
            painter.end();

            painter.begin(&previosImage);
            painter.drawPixmap(0,0,previosPixmap);
            painter.end();

            for(int x = 0; x < w; x++)
                for(int y = 0; y < h; y++)
                {
                    QRgb currentPixel=currentImage.pixel(x,y);
                    QRgb previosPixel=previosImage.pixel(x,y);

                     if(currentPixel==previosPixel)
                     {
                         if(currentPixel!=qRgb(255,255,255))
                            currentImage.setPixel(x,y,qRgb(255,255,255));
                     }
                     else
                         currentImage.setPixel(x,y,qRgb(0,0,0));
                }
            mProcessedData[layer][stripe][channel].setPixmap(QPixmap().fromImage(currentImage));
            mProcessedData[layer][stripe][channel].setDescription( mOriginalData[layer][stripe][channel].getDescription() );
            mProcessedData[layer][stripe][channel].setInformation( mOriginalData[layer][stripe][channel].getInformation() );
        }
    }
}
*/
