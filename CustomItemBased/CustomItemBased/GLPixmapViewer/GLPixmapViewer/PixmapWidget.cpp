#include "PixmapWidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>
#include <QDebug>
#include "structs.h"

#define IMAGE_TEXTURE_GENERATION

PixmapWidget::PixmapWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    mTexture = 0;
}

PixmapWidget::~PixmapWidget()
{
    makeCurrent();
    mGLBuffer.destroy();
    delete mTexture;
    delete mShaderProgram;
    doneCurrent();
}

QSize PixmapWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize PixmapWidget::sizeHint() const
{
    return QSize(200, 200);
}

void PixmapWidget::rotateBy(int angleX, int angleY, int angleZ)
{
    mRotateX += angleX;
    mRotateY += angleY;
    mRotateZ += angleZ;
    update();
}

void PixmapWidget::rotate(int angleX, int angleY, int angleZ)
{
    mRotateX = angleX;
    mRotateY = angleY;
    mRotateZ = angleZ;
    update();
}

void PixmapWidget::translateBy(float translateX, float translateY, float translateZ)
{
    mTranslateX += translateX;
    mTranslateY += translateY;
    mTranslateZ += translateZ;
    update();
}

void PixmapWidget::translate(float translateX, float translateY, float translateZ)
{
    mTranslateX = translateX;
    mTranslateY = translateY;
    mTranslateZ = translateZ;
    update();
}

void PixmapWidget::translate(float translateXYZ)
{
    translate(translateXYZ,translateXYZ,translateXYZ);
}

void PixmapWidget::scale(float scaleXYZ)
{
    scale(scaleXYZ,scaleXYZ,scaleXYZ);
}

void PixmapWidget::scaleBy(float scaleXYZ)
{
    const double minScale=1.0f;
    mScaleX += scaleXYZ;
    mScaleY += scaleXYZ;
    mScaleZ += scaleXYZ;
    if(mScaleX<minScale)mScaleX=minScale;
    if(mScaleY<minScale)mScaleY=minScale;
    if(mScaleZ<minScale)mScaleZ=minScale;

    update();
}

void PixmapWidget::scale(float scaleX, float scaleY, float scaleZ)
{
    mScaleX = scaleX;
    mScaleY = scaleY;
    mScaleZ = scaleZ;
    update();
}

void PixmapWidget::setPixmap(const QPixmap &pixmap)
{
    mPixmap = pixmap;
    makeObject();
    update();
}

void PixmapWidget::setImage(const QImage &image)
{
    mImage = image;
    makeObject();
    update();
}

void PixmapWidget::setBananaGeometry(const BANANA_INFO& geometry)
{
    mBananaGeometry = geometry;
}

void PixmapWidget::setBananaMode(bool mode)
{
    mIsBananaMode = mode;
    makeObject();
    update();
}

BANANA_INFO PixmapWidget::getBananaGeometry()
{
    return mBananaGeometry;
}

void PixmapWidget::initializeOpenGLBuffer(const QVector<GLfloat>& vertData)
{
    mGLBuffer.destroy();
    mGLBuffer.create();
    mGLBuffer.bind();
    mGLBuffer.allocate(sizeof(tVertex)* 2 * (mFacetsNumber+1) );
    if(vertData.size() !=0)
        mGLBuffer.write(0,vertData.constData(),vertData.count() * sizeof(GLfloat));
}

void PixmapWidget::initializeOpenGLShaders()
{
    #define PROGRAM_VERTEX_ATTRIBUTE 0
    #define PROGRAM_TEXCOORD_ATTRIBUTE 1

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    mShaderProgram = new QOpenGLShaderProgram;
    mShaderProgram->addShader(vshader);
    mShaderProgram->addShader(fshader);
    mShaderProgram->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    mShaderProgram->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    mShaderProgram->link();

    mShaderProgram->bind();
    mShaderProgram->setUniformValue("texture", 0);
}

void PixmapWidget::initializeGL()
{
    initializeOpenGLFunctions();
    initializeOpenGLBuffer();
    initializeOpenGLShaders();
    makeObject();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}

void PixmapWidget::paintGL()
{
    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 m;

    float h = geometry().height();
    float w = geometry().width();
    float kx(1.0f), ky(1.0f);
    if(h > w)
        ky = h / w;
    else
        kx = w / h;

    //qDebug()<<"ortho:"<<kx<<ky;
    m.ortho( -kx, kx, ky, -ky, 1.0f, -1.0f);

    m.translate(mTranslateX, mTranslateY, 1.0f);

    m.rotate(mRotateX , 1.0f, 0.0f, 0.0f);
    m.rotate(mRotateY , 0.0f, 1.0f, 0.0f);
    m.rotate(mRotateZ , 0.0f, 0.0f, 1.0f);

    m.scale(mScaleX,mScaleY,1);

    mShaderProgram->setUniformValue("matrix", m);
    mShaderProgram->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    mShaderProgram->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    mShaderProgram->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    mShaderProgram->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

    if(mTexture != nullptr)
        mTexture->bind();

#if(1)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, mVertexes.size());
#else
    glDrawArrays(GL_LINE_STRIP, 0, mVertexes.size());
#endif
}

void PixmapWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void PixmapWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void PixmapWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    //if (event->buttons() & Qt::RightButton)
        //rotateBy(0, 0, 8 * dx);
    if (event->buttons() & Qt::LeftButton)
    {
        float k = qMin(geometry().height(),geometry().width());
        translateBy(2*dx/k,2*dy/k,0.0f);
    }
    lastPos = event->pos();
}

void PixmapWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}

void PixmapWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    scale(1.0f);
    translate(0.0f);
}

void PixmapWidget::wheelEvent(QWheelEvent *event)
{
    scaleBy(event->delta()/1000.0);
}

void PixmapWidget::makeObject()
{
    generateTexture();
    generateVertexes();

    QVector<GLfloat> vertData;

    for(int i=0; i<mVertexes.size(); i++)
    {
        // vertex position
        vertData.append( mVertexes[i].mCoordinates[0]);
        vertData.append( mVertexes[i].mCoordinates[1]);
        vertData.append( mVertexes[i].mCoordinates[2]);
        // texture coordinate
        vertData.append( mVertexes[i].mTextureCoordinates[0]);
        vertData.append( mVertexes[i].mTextureCoordinates[1]);
    }
    initializeOpenGLBuffer(vertData);
}

void PixmapWidget::generateTexture()
{
    if(mTexture)
        delete mTexture;
#ifdef IMAGE_TEXTURE_GENERATION
    if(mImage.isNull() == false)
        mTexture = new QOpenGLTexture(mImage);
#else
    if(mPixmap.isNull() == false)
        mTexture = new QOpenGLTexture(mPixmap.toImage());
#endif
}

QSizeF PixmapWidget::getBoundSize()
{
    if(mIsBananaMode == true)
    {
        float w =  mBananaGeometry.OuterRad - mBananaGeometry.InnerRad * cos( mBananaGeometry.Spread/2 );
        float h = 2 * mBananaGeometry.OuterRad * sin( mBananaGeometry.Spread /2 );

        return QSizeF(w,h);
    }
    else
        #ifdef IMAGE_TEXTURE_GENERATION
        return QSizeF( mImage.size() );
        #else
        return QSizeF( mPixmap.size() );
        #endif
}

void PixmapWidget::generateVertexes()
{
    #define BANAN_IN
    QSizeF size = getBoundSize();
    float x[2],y[2],alfa,dy;
    float h = size.height();
    float w = size.width();
    float kx(1.0f), ky(1.0f), k(1.0f);

    if(mIsBananaMode == true)
    {
        if( h < w )
            ky = h / w;
        else
            kx = w / h;
        k=1.0f/qMax(h,w);
        kx*=k;
        ky*=k;
    }
    else
    {
        if( h < w )
            ky = h / w;
        else
            kx = w / h;
    }

    float step = 1.0/mFacetsNumber;
    float alfaStep = mBananaGeometry.Spread / mFacetsNumber;
    #ifdef BANAN_IN
        double radius[]={mBananaGeometry.InnerRad,mBananaGeometry.OuterRad};
    #else
        double radius[]={mBananaGeometry.OuterRad,mBananaGeometry.InnerRad};
    #endif

    mVertexes.clear();
    for(int i=0; i<=mFacetsNumber; ++i)
    {
        float v = i*step;

        if(mIsBananaMode == true)
        {
            #ifdef BANAN_IN
                alfa = alfaStep * i - ( mBananaGeometry.Spread ) / 2.0f ;
                dy = 1;
            #else
                alfa = alfaStep * i + ( mBananaGeometry.Spread / 2.0f ) + 3.14f / 2.0f;
                dy = -1;
                v = 1 - v;
            #endif
            for(int p=0; p<2; ++p)
            {
                x[p] = radius[p] * cosf( alfa );
                y[p] = radius[p] * sinf( alfa );

                x[p]-= dy*(mBananaGeometry.OuterRad - w / 2.0f);
            }

        }
        else
        {
            y[0] = y[1] = 2 * i * step - 1;
            y[1] = y[0];

            x[0] =-1.0f;
            x[1] =1.0f;
        }

        for(int p = 0; p < 2; ++p)
            mVertexes.push_back( tVertex( x[p]*kx, y[p]*ky, -1, p, v ));
    }
}
