#pragma once
// Plane.h
#include "Point3D.h"
class Plane
{
public:
    Plane();
    Plane(const Point3D& p1, const Point3D& p2, const Point3D& p3);
	~Plane();

    // Getter functions for components of the normal vector
    double normalX() const;
    double normalY() const;
    double normalZ() const;
    Point3D planePoint() const;

private:
    double mNormalX;
    double mNormalY;
    double mNormalZ;

    Point3D mPlanePoint;
};
