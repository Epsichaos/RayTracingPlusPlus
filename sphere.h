#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "point.h"

/*!
* \file sphere.h
* \brief File which contains the class Sphere and all the variables and functions associated
*/

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
	void printSphere();
};

#endif
