#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"

class Object
{
public:
	color getColor(point input_point);
	color getColor();
protected:
	enum m_type {Camera, Light, Cube, Sphere, Mesh};
	Material m_mat;
};

#endif
