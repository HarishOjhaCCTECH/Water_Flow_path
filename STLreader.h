// STLreader.h
#pragma once
#include <vector>
#include <string>
#include "Point3D.h"
#include "Triangle.h"
#include "Triangulation.h"
class STLreader {
public:
    STLreader(); //default constructor
    ~STLreader(); // destructor

    //below function reads from the stl file and stores the points into "lop"(list ofpoints) and in "lot"(list of triangles)
    void comparison(std::string stlFilePath, std::vector<Triangle>& lot, std::vector<Point3D>& lop);

};