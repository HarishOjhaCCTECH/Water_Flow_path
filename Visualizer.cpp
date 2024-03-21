// Visualizer.cpp
#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"
#include <limits>
#include "double_comparison.h"

Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
    triguObj = new Triangulation();
}

Visualizer::~Visualizer()
{}

void Visualizer::setupUi() 
{
    resize(600, 600);
    mMenuBar = new QMenuBar(this);
    setMenuBar(mMenuBar);
    mMainToolBar = new QToolBar(this);
    addToolBar(mMainToolBar);
    mStatusBar = new QStatusBar(this);
    setStatusBar(mStatusBar);

    mGridLayout = new QGridLayout(this);

    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mGridLayout->addWidget(mRenderer, 0, 0, 100, 8);


    mLoadStlButton = new QPushButton("Load STL", this);
    mGridLayout->addWidget(mLoadStlButton, 19, 8, 1, 1);

    // add button
    mAddButton = new QPushButton("Add", this);
    mGridLayout->addWidget(mAddButton, 29, 8, 1, 1);

    // central widget
    mWidget = new QWidget(this);
    mWidget->setLayout(mGridLayout);
    setCentralWidget(mWidget);

    connect(mAddButton, &QPushButton::clicked, this, &Visualizer::onAddButtonClicked);
    connect(mLoadStlButton, &QPushButton::clicked, this, &Visualizer::onLoadStlButtonClicked);

    setWindowTitle(QCoreApplication::translate("Visualiser", "Visualiser", nullptr));
}

void Visualizer::onAddButtonClicked()
{
    //droplet start
    // 19.57671933333333 50 18.29286933333333
    double xValue = 19.57671933333333;
    double yValue = 18.783069;
    double zValue = 100;

    Point3D dropletStart(xValue, yValue, zValue);
    // adding the starting point to Droplet vertices list for rendering
    mRenderer->mDropletVers.push_back(xValue);
    mRenderer->mDropletVers.push_back(yValue);
    mRenderer->mDropletVers.push_back(zValue);

    // droplet line equation
    l = new Line(Point3D(xValue, yValue, zValue), Point3D(xValue, yValue, zValue-1));

    // Triangle plane on which droplet falls
    Point3D a(19.444444, 19.047619, 18.192773);
    Point3D b(19.444444, 18.650794, 18.284387);
    Point3D c(19.841270, 18.650794, 18.401448);

    // plane's equaton
    Plane pl(a,b,c);

    Point3D dropletTouchingLand = g->findIntersection(*l, pl);

    mRenderer->setDropletAttributes(dropletTouchingLand);
    mRenderer->update();

    // finding lowest point in triangle plane
    Point3D currentLowestPoint = g->findLowestVertex(a,b,c);
    Point3D nextLowestPoint;
    //mRenderer->setDropletAttributes(currentLowestPoint);
    //mRenderer->update();

    vector<Point3D> startingTrianglePoints ={a,b,c};
    Triangle startingTriangle(0, 1, 2);

    

    // finding next 5 triangles for going into next triangle
    int currentPointPosition = 0;
    Triangulation fiveNeighbours;

    //loop to find the 5 neighbours
    int loopItrNum = 0;
    for (auto& k : triguObj->listOfTriangles()) { 

        float lowX = currentLowestPoint.x();
        float lowY = currentLowestPoint.y();
        float lowZ = currentLowestPoint.z();
        if (
            (
                AreDoubleSame(lowX, (triguObj->listOfPoints()[k.v1()].x()))
                &&
                AreDoubleSame(lowY, (triguObj->listOfPoints()[k.v1()].y()))
                &&
                AreDoubleSame(lowZ, (triguObj->listOfPoints()[k.v1()].z()))
            )

            ||

            (

                AreDoubleSame(lowX, (triguObj->listOfPoints()[k.v2()].x()))
                &&
                AreDoubleSame(lowY, (triguObj->listOfPoints()[k.v2()].y()))
                &&
                AreDoubleSame(lowZ, (triguObj->listOfPoints()[k.v2()].z()))
            )

            ||

            (
                AreDoubleSame(lowX, (triguObj->listOfPoints()[k.v3()].x()))
                &&
                AreDoubleSame(lowY, (triguObj->listOfPoints()[k.v3()].y()))
                &&
                AreDoubleSame(lowZ, (triguObj->listOfPoints()[k.v3()].z()))
            )
           )
        {
            fiveNeighbours.listOfPoints().push_back(
                Point3D((triguObj->listOfPoints()[k.v1()].x()), (triguObj->listOfPoints()[k.v1()].y()), (triguObj->listOfPoints()[k.v1()].z()))
            );

            fiveNeighbours.listOfPoints().push_back(
                Point3D((triguObj->listOfPoints()[k.v2()].x()), (triguObj->listOfPoints()[k.v2()].y()), (triguObj->listOfPoints()[k.v2()].z()))
            );

            fiveNeighbours.listOfPoints().push_back(
                Point3D((triguObj->listOfPoints()[k.v3()].x()), (triguObj->listOfPoints()[k.v2()].y()), (triguObj->listOfPoints()[k.v3()].z()))
            );

            fiveNeighbours.listOfTriangles().push_back(Triangle(currentPointPosition, currentPointPosition + 1, currentPointPosition + 2));
            currentPointPosition = currentPointPosition + 3;
        }

        if (fiveNeighbours.listOfTriangles().size() == 6)
        { 
            //remove 6th triangle which is starting triangle
            int i = 0;
            for (auto& k : fiveNeighbours.listOfTriangles()) {
                if (a.x() == fiveNeighbours.listOfPoints()[k.v1()].x() && b.x() == fiveNeighbours.listOfPoints()[k.v2()].x() && c.x() == fiveNeighbours.listOfPoints()[k.v3()].x())
                {
                    fiveNeighbours.listOfTriangles().erase(fiveNeighbours.listOfTriangles().begin() + i);
                    fiveNeighbours.listOfPoints().erase(fiveNeighbours.listOfPoints().begin() + (i * 3) + 1, fiveNeighbours.listOfPoints().begin() + (i * 3) + 4);
                    break;
                }
                i++;
            }
            currentPointPosition = 0;
            break; 
        }        
        loopItrNum++;
    }

    // now finding the lowest vertex among 5 triangles


    nextLowestPoint = triguObj->findinglowestPointfromneighbours(fiveNeighbours);

   
    // Initial stage is completed
    
    // now the loop for continuous searching will start
    mRenderer->setDropletAttributes(currentLowestPoint);
    mRenderer->setDropletAttributes(nextLowestPoint);
    Point3D furtherLowestPoint;
    for (int i = 0; i < 127502; i++)
    {

        // this tempTrigu contains 4 triangles
        Triangulation tempTrigu1 = triguObj->searching(currentLowestPoint, nextLowestPoint);
        
        double furtherLowestY = std::numeric_limits<double>::max();
        for (auto& k : tempTrigu1.listOfPoints())
        {
            if (furtherLowestY > k.z())
            {
                furtherLowestY = k.z();
                furtherLowestPoint = Point3D(k.x(), k.y(), k.z());
            }
        }

        mRenderer->setDropletAttributes(furtherLowestPoint);

        
        //Triangulation tempTrigu2 = triguObj->finding2neighbours(tempTrigu1, furtherLowestPoint);
        
        
        
        currentLowestPoint = nextLowestPoint;
        nextLowestPoint = furtherLowestPoint;
        
    }
    mRenderer->mDropletVers.push_back(0);
    mRenderer->mDropletVers.push_back(0);
    mRenderer->mDropletVers.push_back(0);
    for (int j = 0; j < (mRenderer->mDropletVers.size())/3; j++)
    {
        mRenderer->mDropletColors.push_back(1);
        mRenderer->mDropletColors.push_back(0);
        mRenderer->mDropletColors.push_back(0);
    }


    mRenderer->update();
}

void Visualizer::onLoadStlButtonClicked()
{
    
    

    stlReaderObj.comparison("D:/harish_ojha_workspace/cpp_assignments/old_material/assign_3-stl_reader/STLfiles/Terrain.stl", triguObj->listOfTriangles(), triguObj->listOfPoints()); 
    
    for (auto& k : triguObj->listOfTriangles())
    {
        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v1()].x());
        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v1()].y());
        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v1()].z());

        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v2()].x());
        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v2()].y());
        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v2()].z());

        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v3()].x());
        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v3()].y());
        mRenderer->mStlVertices.push_back((float)triguObj->listOfPoints()[k.v3()].z());


        for (int i = 0; i < 9; i++)
        {

            mRenderer->mStlColors.push_back(1);
        }
    }
    mRenderer->update();

}

