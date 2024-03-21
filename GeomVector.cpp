// GeomVector.cpp
#include "stdafx.h"
#include "GeomVector.h"
GeomVector::GeomVector() {}
GeomVector::~GeomVector() {}


// Function to calculate the intersection point of a line and a plane
Point3D GeomVector::findIntersection(const Line& line, const Plane& plane) {
    Point3D linePoint = line.getPoint();
    Point3D lineDirection = line.getDirection();

    // Calculate dot product of plane normal and line direction
    double dotProduct = plane.normalX() * lineDirection.x() +
        plane.normalY() * lineDirection.y() +
        plane.normalZ() * lineDirection.z();

    // If dot product is 0, line is parallel to plane and there is no intersection
    if (std::abs(dotProduct) < 1e-6) {
        return { 0, 0, 0 }; // Return a default point indicating no intersection
    }

    // Calculate parameter t for the line equation: linePoint + t * lineDirection
    Point3D tempPlanePoint = plane.planePoint();
    double t = ((tempPlanePoint.x() - linePoint.x()) * plane.normalX() +
        (tempPlanePoint.y() - linePoint.y()) * plane.normalY() +
        (tempPlanePoint.z() - linePoint.z()) * plane.normalZ()) / dotProduct;

    // Calculate the intersection point
    Point3D intersectionPoint;
    intersectionPoint.setX(linePoint.x() + t * lineDirection.x());
    intersectionPoint.setY(linePoint.y() + t * lineDirection.y());
    intersectionPoint.setZ(linePoint.z() + t * lineDirection.z());

    return intersectionPoint;
}

// Function to find the index of the lowest vertex in a triangle
Point3D GeomVector::findLowestVertex(const Point3D& v1, const Point3D& v2, const Point3D& v3)
{
    double lowest = v1.y();
    int lowestIndex = 1;
    if (lowest > v2.z())
    {
        lowest = v2.z();
        lowestIndex = 2;
    }
    else if(lowest > v3.z())
    {
        lowest = v3.z();
        lowestIndex = 3;
    }
    

    if (lowestIndex == 1)
    {
        return v1;
    }
    else if (lowestIndex == 2)
    {
        return v2;
    }
    else
    {
        return v3;
    }
}