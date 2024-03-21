#pragma once
// Line.h
#include "Point3D.h"
class Line
{
public:
    Line();
	Line(const Point3D& p1, const Point3D& p2);
	~Line();

    // Getter functions for the point and direction of the line
    Point3D getPoint() const;
    Point3D getDirection() const;

private:
    Point3D point; // A point on the line
    Point3D direction; // Direction vector of the line
};