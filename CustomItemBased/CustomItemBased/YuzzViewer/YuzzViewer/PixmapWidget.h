#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QVector>
#include <QSize>
#include "structs.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

struct tVertex{
    tVertex(){}
    tVertex(GLfloat x,GLfloat y, GLfloat z,GLfloat u,GLfloat v)
    {
        mCoordinates[0] = x;
        mCoordinates[1] = y;
        mCoordinates[2] = z;

        mTextureCoordinates[0] = u;
        mTextureCoordinates[1] = v;
    }
    GLfloat mCoordinates[3]{0,0,0};
    GLfloat mTextureCoordinates[2]{0,0};
};

struct tBananaGeomatry{
    tBananaGeomatry(){}
    tBananaGeomatry(GLdouble inRadius,GLdouble outRadius,GLdouble spread)
        :mInRadius(inRadius),mOutRadius(outRadius),mSpread(spread)
    {}
    double mInRadius{730};
    double mOutRadius{1500};
    double mSpread{1.57};
};

class PixmapWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit PixmapWidget(QWidget *parent = 0);
    ~PixmapWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    void translateBy(float translateX, float translateY, float translateZ);
    void translate(float translateX, float translateY, float translateZ);
    void translate(float translateXYZ);

    void rotateBy(int angleX, int angleY, int angleZ);
    void rotate(int angleX, int angleY, int angleZ);

    void scaleBy(float scaleXYZ);
    void scale(float scaleXYZ);
    void scale(float scaleX, float scaleY, float scaleZ);

    void setPixmap(const QPixmap& pixmap);
    void setImage(const QImage& image);
    void setBananaGeometry(const BANANA_INFO& geometry);
    void setBananaMode(bool mode);

    BANANA_INFO getBananaGeometry();

    QSizeF getBoundSize();
signals:
    void clicked();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:
    void makeObject();
    void generateVertexes();
    void generateTexture();
    void initializeOpenGLBuffer(const QVector<GLfloat>& vertData = QVector<GLfloat>());
    void initializeOpenGLShaders();
    QColor clearColor{Qt::gray};
    QPoint lastPos;
    int mRotateX{0};
    int mRotateY{0};
    int mRotateZ{0};
    float mScaleX{1.0f};
    float mScaleY{1.0f};
    float mScaleZ{1.0f};
    float mTranslateX{0.0f};
    float mTranslateY{0.0f};
    float mTranslateZ{0.0f};
    bool mIsBananaMode{false};
    int mFacetsNumber{256};
	BANANA_INFO mBananaGeometry;
    QPixmap mPixmap;
    QImage mImage;
    QVector<tVertex> mVertexes;
    QOpenGLTexture* mTexture;
    QOpenGLShaderProgram* mShaderProgram;
    QOpenGLBuffer mGLBuffer;
};

#endif // PIXMAPWIDGET_H
