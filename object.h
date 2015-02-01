#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"

class Object
{
public:
protected:
	enum m_type {Camera, Light, Cube, Sphere, Mesh};
	Material m_mat;
};

#endif
