#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "color.h"
#include "point.h"
#include "struct.h"
#include <string>

class Object
{
public:
	Color getColor(Point input_point);
	Color getColor();
	std::string getType(std::string input);
	void setColorObject(Color);
	void setTypeObject(std::string);
protected:
	//type_object m_type;
	//enum m_type {Camera, Light, Cube, Sphere, Mesh};
	int m_type;
	Material m_mat;
};

#endif
