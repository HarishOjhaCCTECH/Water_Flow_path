// Triangulation.cpp
#include "stdafx.h"
#include"Triangulation.h"
#include <vector>
#include "double_comparison.h"
Triangulation::Triangulation() {} // default constructor
Triangulation::~Triangulation() {} // destructor
std::vector<Triangle>& Triangulation::listOfTriangles() { // getter
    return mListOflistOfTriangles;
}
std::vector<Point3D>& Triangulation::listOfPoints() { // getter
    return mUniquelistOfPoints;
}

//searches next four triangles
Triangulation Triangulation::searching(Point3D previousLowest, Point3D currentLowest)
{
    Triangulation result;
    int currentPointPos = 0;

    double lowX = currentLowest.x();
    double lowY = currentLowest.y();
    double lowZ = currentLowest.z();

    for (auto& k : mListOflistOfTriangles) {
        if (
            (
                AreDoubleSame(lowX, (listOfPoints()[k.v1()].x()))
                &&
                AreDoubleSame(lowY, (listOfPoints()[k.v1()].y()))
                &&
                AreDoubleSame(lowZ, (listOfPoints()[k.v1()].z()))
                )

            ||

            (

                AreDoubleSame(lowX, (listOfPoints()[k.v2()].x()))
                &&
                AreDoubleSame(lowY, (listOfPoints()[k.v2()].y()))
                &&
                AreDoubleSame(lowZ, (listOfPoints()[k.v2()].z()))
                )

            ||

            (
                AreDoubleSame(lowX, (listOfPoints()[k.v3()].x()))
                &&
                AreDoubleSame(lowY, (listOfPoints()[k.v3()].y()))
                &&
                AreDoubleSame(lowZ, (listOfPoints()[k.v3()].z()))
                )
            )
        {
            result.listOfPoints().push_back(
                Point3D((listOfPoints()[k.v1()].x()), (listOfPoints()[k.v1()].y()), (listOfPoints()[k.v1()].z()))
            );

            result.listOfPoints().push_back(
                Point3D((listOfPoints()[k.v2()].x()), (listOfPoints()[k.v2()].y()), (listOfPoints()[k.v2()].z()))
            );

            result.listOfPoints().push_back(
                Point3D((listOfPoints()[k.v3()].x()), (listOfPoints()[k.v2()].y()), (listOfPoints()[k.v3()].z()))
            );

            result.listOfTriangles().push_back(Triangle(currentPointPos, currentPointPos + 1, currentPointPos + 2));
            currentPointPos = currentPointPos + 3;
        }

        if (result.listOfTriangles().size() == 6)
        {
            //remove 6th triangle which is starting triangle
            int i = 0;
            double pLowX = previousLowest.x();
            double pLowY = previousLowest.y();
            double pLowZ = previousLowest.z();
            while(i<result.listOfTriangles().size()){
                if (
                    (AreDoubleSame(pLowX, result.listOfPoints()[result.listOfTriangles()[i].v1()].x()) && AreDoubleSame(pLowY, result.listOfPoints()[result.listOfTriangles()[i].v1()].y()) && AreDoubleSame(pLowZ, result.listOfPoints()[result.listOfTriangles()[i].v1()].z()))
                    ||
                    (AreDoubleSame(pLowX, result.listOfPoints()[result.listOfTriangles()[i].v2()].x()) && AreDoubleSame(pLowY, result.listOfPoints()[result.listOfTriangles()[i].v2()].y()) && AreDoubleSame(pLowZ, result.listOfPoints()[result.listOfTriangles()[i].v2()].z()))
                    ||
                    (AreDoubleSame(pLowX, result.listOfPoints()[result.listOfTriangles()[i].v3()].x()) && AreDoubleSame(pLowY, result.listOfPoints()[result.listOfTriangles()[i].v3()].y()) && AreDoubleSame(pLowZ, result.listOfPoints()[result.listOfTriangles()[i].v3()].z()))
                    )
                {
                    result.listOfTriangles().erase(result.listOfTriangles().begin() + i);
                    result.listOfPoints().erase(result.listOfPoints().begin() + (i * 3) + 1, result.listOfPoints().begin() + (i * 3) + 4);
                    continue;
                }
                i++;
                
            }   
        }
    }
    return result;


}
Point3D Triangulation::findinglowestPointfromneighbours(Triangulation& t)
{
    Point3D result;
    double nextLowestY = std::numeric_limits<double>::max(); // result.listOfPoints()[neigbhouringTriangles[0].v1()].y();
    for (auto& k : t.listOfPoints())
    {
        if (nextLowestY > k.z())
        {
            nextLowestY = k.z();
            result = Point3D(k.x(), k.y(), k.z());
        }
    }
    return result;
}