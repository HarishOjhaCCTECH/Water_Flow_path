// OpenGLWindow.cpp
#include "stdafx.h"
#include "OpenGLWindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <iostream>


OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) :
    mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}
OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    // And now release all OpenGL resources.
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(-10.0f * zoomScale, 10.0f * zoomScale, -10.0f * zoomScale, 10.0f * zoomScale, 0.1f, 100.0f);

    matrix.translate(0, 0, -10);
    matrix.rotate(rotationX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    matrix.rotate(rotationY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis
    mProgram->setUniformValue(m_matrixUniform, matrix);

    
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mStlVertices.data());
    glVertexAttribPointer(m_colAttr, 3, GL_INT, GL_FALSE, 0, mStlColors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_LINE_LOOP, 0, mStlVertices.size() / 3);
    
    QVector<GLfloat> points;
    points <<100 << 0 << 0;
    points << 0 << 100 << 0;
    points << 0 << 0 << 100;
    points << 0 << 0 << 0;
    colors.clear();

    colors << 1 << 0 << 0;
    colors << 0 << 1 << 0;
    colors << 0 << 0 << 1;
    colors << 1 << 1 << 1;
    
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mDropletVers.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mDropletColors.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);
    glEnable(GL_PROGRAM_POINT_SIZE);

    glDrawArrays(GL_POINTS, 0, mDropletVers.size() / 3);

    glDisableVertexAttribArray(m_posAttr);
    glDisableVertexAttribArray(m_colAttr);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glFlush();
}


void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_PointSize = 10.0;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);

}

void OpenGLWindow::wheelEvent(QWheelEvent* event) {
    if (event->angleDelta().y() > 0) {
        zoomScale *= 1.1f;
    }
    else {
        zoomScale /= 1.1f;
    }
    update(); // This will trigger a repaint of the widget
}

void OpenGLWindow::mousePressEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        lastPos = event->pos();
    }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        rotationX -= dy / 3.0f;
        rotationY -= dx / 3.0f;

        update();
        lastPos = event->pos();
    }
}

void OpenGLWindow::setRendererAttributes(Point3D& start, Point3D& end, Point3D& triVertex)
{
    lineVertices.clear();

    lineVertices.push_back(start.x());
    lineVertices.push_back(start.y());
    lineVertices.push_back(start.z());

    lineVertices.push_back(end.x());
    lineVertices.push_back(end.y());
    lineVertices.push_back(end.z());

    //
    lineVertices.push_back(end.x());
    lineVertices.push_back(end.y());
    lineVertices.push_back(end.z());

    lineVertices.push_back(triVertex.x());
    lineVertices.push_back(triVertex.y());
    lineVertices.push_back(triVertex.z());
}

vector<float> OpenGLWindow::stlVertices() { return mStlVertices; }

vector<int> OpenGLWindow::stlColors() { return mStlColors; }

void OpenGLWindow::setDropletAttributes(Point3D& p)
{
    mDropletVers.push_back(p.x());
    mDropletVers.push_back(p.y());
    mDropletVers.push_back(p.z());

    mDropletVers.push_back(p.x());
    mDropletVers.push_back(p.y());
    mDropletVers.push_back(p.z());
}