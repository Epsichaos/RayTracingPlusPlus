#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "point.h"

class Ray
{
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
