#ifndef MESH_H
#define MESH_H

#include "face.h"
#include "vector.h"
#include "object.h"
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
	~Mesh();
	void setNumberofFace(unsigned int);
	unsigned int getNumberOfFace();
	void defineFaces(Face*, unsigned int);
	void defineNormales(Vector*, unsigned int);
	void getFaceArray(Face*);
	void getNormalesArray(Vector*);
protected:
	unsigned int m_number_of_faces;
	Face *m_faces;
	Vector *m_normales;
};

#endif
