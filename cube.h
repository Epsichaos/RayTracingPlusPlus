#ifndef CUBE_H
#define CUBE_H

#include "point.h"
#include "object.h"

class Cube : public Object
{
protected:
	Point m_p1;
	Point m_p2;
	Point m_p3;
	Point m_p4;
	Point m_p5;
	Point m_p6;
	Point m_p7;
	Point m_p8;
public:
	Cube();
	Cube(Point, Point, Point, Point, Point, Point, Point, Point);
	void setCube(Point, Point, Point, Point, Point, Point, Point, Point);
	void printCube();
};

#endif
