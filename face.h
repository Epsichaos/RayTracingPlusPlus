#ifndef FACE_H
#define FACE_H

#include "point.h"
#include "material.h"
#include "vector.h"

/*!
* \file face.h
* \brief File which contains the class Face and all the variables and functions associated. The class Face will
* only be used in the class Mesh, which aim is to read a .obj file and to render it in raytracing.
*/

/*!
* \class Face
* \brief Define a Face by 3 points and a material
*/
class Face
{
public:
	/*!
	* \brief Default constructor
	*/
	Face();
	/*!
	* \brief Constructor, without material
	* \param Point_1 First point of the face
	* \param Point_2 Second point of the face
	* \param Point_3 Third point of the face
	*/
	Face(Point, Point, Point);
	/*!
	* \brief Constructor with material
	* \param Point_1 First point of the face
	* \param Point_2 Second point of the face
	* \param Point_3 Third point of the face
	* \param Mat Material of the face
	*/
	Face(Point, Point, Point, Material);
	/*!
	* \brief Redefine the points of the face
	* \param Point_1 First point of the face
	* \param Point_2 Second point of the face
	* \param Point_3 Third point of the face
	*/
	void setFace(Point, Point, Point);
	/*! 
	* \brief Accessor to the first point of the face
	* \return Point
	*/
	Point p1();
	/*! 
	* \brief Accessor to the second point of the face
	* \return Point
	*/
	Point p2();
	/*! 
	* \brief Accessor to the third point of the face
	* \return Point
	*/
	Point p3();
	/*! 
	* \brief Accessor to one vector of the face
	* \return Vector
	*/
	Vector v1();
	/*! 
	* \brief Accessor to another vector of the face
	* \return Vector
	*/
	Vector v2();
	/*! 
	* \brief Accessor to the color of the face
	* \return Color
	*/
	Color getColor();
	/*! 
	* \brief Redefine the color of a face
	* \param Color The new color
	*/
	void setColor(Color);
	/*! 
	* \brief Accessor to the diffuse factor
	* \return Diffuse_Factor The diffuse factor
	*/	
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
