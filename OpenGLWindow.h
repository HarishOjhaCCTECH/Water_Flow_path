#pragma once
// OpenGLWindow.h
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "Point3D.h"

using namespace std;
class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;

class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

    void setRendererAttributes(Point3D& start, Point3D& end, Point3D& triVertex);
    void setDropletAttributes(Point3D& p);
    vector<float> stlVertices();
    vector<int> stlColors();
    vector<float> mStlVertices;
    vector<int> mStlColors;
    vector<float> mDropletVers;
    vector<int> mDropletColors;

protected:
    void paintGL() override;
    void initializeGL() override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void reset();

private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLPaintDevice* mDevice = nullptr;

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;

    
    QList<QVector3D> mNormals;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;

    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    float zoomScale = 1.0f;

    QVector<GLfloat> vertices;
    QVector<GLfloat> colors;
    QMatrix4x4 matrix;
    QPoint lastPos;
    float rotationX = 0.0f;
    float rotationY = 0.0f;

    vector<double> lineVertices;

};