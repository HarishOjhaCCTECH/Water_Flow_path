// Plane.cpp

#include "stdafx.h"
#include "Plane.h"

Plane::Plane() {}

Plane::Plane(const Point3D& p1, const Point3D& p2, const Point3D& p3)
{
    // Calculate vectors lying on the plane
    double v1x = p2.x() - p1.x();
    double v1y = p2.y() - p1.y();
    double v1z = p2.z() - p1.z();

    double v2x = p3.x() - p1.x();
    double v2y = p3.y() - p1.y();
    double v2z = p3.z() - p1.z();

    // Calculate cross product of v1 and v2 to find the normal vector
    mNormalX = v1y * v2z - v1z * v2y;
    mNormalY = v1z * v2x - v1x * v2z;
    mNormalZ = v1x * v2y - v1y * v2x;

    // Normalize the normal vector
    double magnitude = std::sqrt(mNormalX * mNormalX + mNormalY * mNormalY + mNormalZ * mNormalZ);
    mNormalX /= magnitude;
    mNormalY/= magnitude;
    mNormalZ /= magnitude;

    mPlanePoint.setX(p1.x());
    mPlanePoint.setY(p1.y());
    mPlanePoint.setZ(p1.z());
}

Plane::~Plane() {}

// Getter functions for components of the normal vector
double Plane::normalX() const { return mNormalX; }
double Plane::normalY() const { return mNormalY; }
double Plane::normalZ() const { return mNormalZ; }

Point3D Plane::planePoint() const { return mPlanePoint; }
