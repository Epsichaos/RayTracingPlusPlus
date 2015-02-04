#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "color.h"
#include "point.h"

class Object
{
public:
	Color getColor(Point input_point);
	Color getColor();
protected:
	enum m_type {Camera, Light, Cube, Sphere, Mesh};
	Material m_mat;
};

#endif
