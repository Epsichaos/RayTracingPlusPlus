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
<<<<<<< HEAD
protected: 
=======
protected:
>>>>>>> c6f558d7f1c28b4d57fff4daf3680ec4141eeb95
	unsigned int m_number_of_faces;
	Face *m_faces;
};

#endif
