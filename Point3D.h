#pragma once
// Point3D.h
class Point3D
{
public:
	Point3D();
	Point3D(double inX, double inY, double inZ);
	~Point3D();

	double x() const;
	double y() const;
	double z() const;

	void setX(double inX);
	void setY(double inY);
	void setZ(double inZ);

	// custom operator is needed here to make it usable in map datastructure
	bool operator<(const Point3D& other) const;

private:
	double mX;
	double mY;
	double mZ;
};