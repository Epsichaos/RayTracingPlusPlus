#ifndef MESH_H
#define MESH_H

#include "face.h"
/*!
* \file mesh.h
* \brief File which contains the class Mesh and all the variables and functions associated
*/

/*!
* \class Mesh
* \brief Derivated of the class Object, the class Mesh define what a mesh is
*/
class Mesh : public Object
{
public:
	Mesh();
	void setNumberofFace(unsigned int);
	Point getNumberOfFace();
	void defineFaces(Face*, unsigned int);
	Face* getFaceArray();
protected:
	unsigned int m_number_of_faces;
	Face *m_faces;
};

#endif
