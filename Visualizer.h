// Visualizer.h
#pragma once

#include <vector>
#include <QtWidgets/QMainWindow>
#include "Visualizer.h"
#include "Line.h"
#include "Point3D.h"
#include "Plane.h"
#include "GeomVector.h"
#include "STLreader.h"
#include "Triangle.h"
#include "Triangulation.h"

class OpenGLWindow;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();

private:
    void setupUi();

private slots:
    void onAddButtonClicked();
    
    void onLoadStlButtonClicked();

private:
    QMenuBar* mMenuBar;
    QToolBar* mMainToolBar;
    QWidget* mCentralWidget;
    QStatusBar* mStatusBar;
    OpenGLWindow* mRenderer;
    QGridLayout* mGridLayout;
    
    QPushButton* mAddButton;


    

    QWidget* mWidget;
    QPushButton* mLoadStlButton;

    Line* l;
    GeomVector* g;

    Triangulation* triguObj; // object "triguObj" is created to store the Points and Triangles in vector
    STLreader stlReaderObj; // object "stlReaderObj" is created to convert the stl and store in structured way

    
};