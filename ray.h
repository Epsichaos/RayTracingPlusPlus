#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "point.h"

/*!
* \file ray.h
* \brief File which contains the class Ray and all the variables and functions associated
*/

class Ray {
public:
	Ray();
	Ray(Point const A, Vector const B);
	Vector getDirection();
	void setStart(Point const A);
	void setDirection(Vector const A);
protected:
	Point m_start;
	Vector m_direction;
};

#endif
