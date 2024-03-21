
#pragma once
// GeomVector.h
#include "Point3D.h"
#include "Line.h"
#include "Plane.h"
class GeomVector
{
public:
	GeomVector();
	~GeomVector();

    Point3D findIntersection(const Line& line, const Plane& planeNormal);
	Point3D findLowestVertex(const Point3D& v1, const Point3D& v2, const Point3D& v3);
};