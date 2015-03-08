#ifndef FACE_H
#define FACE_H

#include "point.h"
#include "material.h"
#include "vector.h"

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
public:
	Face();
	Face(Point, Point, Point);
	Face(Point, Point, Point, Material);
	void setFace(Point, Point, Point);
	Point p1();
	Point p2();
	Point p3();
	Vector v1();
	Vector v2();
	Color getColor();
	void setColor(Color);
	double getDiffuseFactor();
protected:
	/*!
	* \brief First point of the face
	*/
	Point m_p1;
	/*!
	* \brief Second point of the face
	*/
	Point m_p2;
	/*!
	* \brief Last point of the face
	*/
	Point m_p3;
	/*!
	* \brief Material of the face
	*/
	Material m_m1;
};

#endif
