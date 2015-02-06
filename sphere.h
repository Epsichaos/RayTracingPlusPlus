#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "point.h"

class Sphere : public Object
{
protected:
	Point m_center;
	double m_radius;
public:
	Sphere();
	Sphere(Point, double);
	void setCenter(Point);
	void setRadius(double);
	double getRadius();
};

#endif
