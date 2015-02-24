#ifndef FACE_H
#define FACE_H

/*!
* \file face.h
* \brief File which contains the class Face and all the variables and functions associated
*/

/*!
* \class Face
* \brief Define a Face by 3 points and a material
*/
class Face
{
protected:
	/*!
	* \brief First point of the face
	*/
	point m_p1;
	/*!
	* \brief Second point of the face
	*/
	point m_p2;
	/*!
	* \brief Last point of the face
	*/
	point m_p3;
	/*!
	* \brief Material of the face
	*/
	material m_m1;
};

#endif
