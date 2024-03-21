// Triangulation.h
#pragma once
#include <vector>
#include "Triangle.h"
#include "Point3D.h"
class Triangulation {
public:
    Triangulation(); // default constructor
    ~Triangulation(); // destructor
    std::vector<Triangle>& listOfTriangles();// getter
    std::vector<Point3D>& listOfPoints();//getter


    // it searching 4 neighbours 
    Triangulation searching(Point3D previousLowest, Point3D currentLowest);
    Point3D findinglowestPointfromneighbours(Triangulation& t);
    
private:
    std::vector<Triangle> mListOflistOfTriangles; // storage area for all the Triangles object
    std::vector<Point3D> mUniquelistOfPoints; // storage area for all the Points object
};