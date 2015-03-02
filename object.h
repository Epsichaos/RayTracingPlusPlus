#ifndef OBJECT_H
#define OBJECT_H

#include "material.h"
#include "color.h"
#include "point.h"
#include "struct.h"
#include <string>

/*!
* \file object.h
* \brief File which contains the class Object and all the variables and functions associated
*/

/*! \class Object
* \brief Class used to store objects.
* Objects can be everything : sphere, cubes, or whatever. This class will most of the time not be used. We will use the
* derivatives classes from the class Object.
*/
class Object
{
public:
	/*!
	* \brief Accessor to the color of an object
	* \return The color of the object
	*/
	Color getColor();
	/*!
	* \brief Accessor to the type of an object
	* \return The string of the type of the object : *camera*, *light*, *sphere* or *cube*
	*/
	std::string getType(std::string input);
	/*!
	* \brief Set the color of the object
	* \param color. Set **color** as the new color of the object
	*/
	void setColorObject(Color);
	/*!
	* \brief Set the type of the object
	* \param Str. Str can be *camera*, *sphere*, *cube* or *light*
	*/
	void setTypeObject(std::string);
	/*!
	* \fn std::string getType()
	* \brief return the type of the object
	*/
	std::string getType();
	double getDiffuseFactor();
protected:
	//type_object m_type;
	//enum m_type {Camera, Light, Cube, Sphere, Mesh};
	/*!
	* \brief Int which give the type of object. By convention *camera* = 0, *light* = 1, *cube* = 2, *sphere* = 3 and *mesh* = 4
	*/
	int m_type;
	/*!
	* \brief Describe the type of material of the object. The color, and the refraction and reflexion values
	*/
	Material m_mat;
};

#endif
