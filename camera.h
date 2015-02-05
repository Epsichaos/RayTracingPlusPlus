#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "object.h"
#include "point.h"

class Camera : public Object {
public:
	void setPosition(Point);
	void setDirection(Vector);
	void setSize(int, int);
	void setAngle(double);
	void printCamera();
protected:
	Point m_position;
	Vector m_direction;
	int m_width;
	int m_height;
	double m_angle;
};

#endif
