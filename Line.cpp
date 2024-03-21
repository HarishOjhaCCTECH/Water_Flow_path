// Line.cpp
#include "stdafx.h"
#include "Line.h"

Line::Line() {}

Line::Line(const Point3D& p1, const Point3D& p2) {
    point = p1;

    double directX = p2.x() - p1.x();
    double directY = p2.y() - p1.y();
    double directZ = p2.z() - p1.z();

    // Normalize the direction vector
    double magnitude = std::sqrt(directX * directX + directY * directY + directZ * directZ);
    directX /= magnitude;
    directY /= magnitude;
    directZ /= magnitude;
    direction.setX(directX);
    direction.setY(directY);
    direction.setZ(directZ);
}

Line::~Line() {}

// Getter functions for the point and direction of the line
Point3D Line::getPoint() const { return point; }
Point3D Line::getDirection() const { return direction; }
