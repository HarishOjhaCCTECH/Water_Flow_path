// Point3D.cpp

#include "stdafx.h"
#include "Point3D.h"
Point3D::Point3D(): mX(0), mY(0), mZ(0){}
Point3D::Point3D(double inX, double inY, double inZ) : mX(inX), mY(inY), mZ(inZ) {}
Point3D::~Point3D() {}

double Point3D::x()  const { return mX; }
double Point3D::y()  const { return mY; }
double Point3D::z()  const { return mZ; }


void Point3D::setX(double inX) { mX = inX; }
void Point3D::setY(double inY) { mY = inY; }
void Point3D::setZ(double inZ) { mZ = inZ; }

bool Point3D::operator<(const Point3D& other) const { // operator overloading is necessary here, so that Point datatype can be used in map
    if (mX != other.mX) return mX < other.mX;
    if (mY != other.mY) return mY < other.mY;
    return mZ < other.mZ;
}
