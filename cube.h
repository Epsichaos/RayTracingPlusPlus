#ifndef CUBE_H
#define CUBE_H

#include "point.h"
#include "object.h"

/*!
* \file cube.h
* \brief File which contains the class Cube and all the variables and functions associated
*/

/*! \class Cube
* \brief Contains the description of a Cube object
* This class, derivated from the class Object define what a cube is. We will define the cube by
* its 8 corners.
*/
class Cube : public Object
{
protected:
	/*!
	* \brief Corner 1 over 8 defined by a point in the 3D space
	*/
	Point m_p1;
	/*!
	* \brief Corner 2 over 8 defined by a point in the 3D space
	*/
	Point m_p2;
	/*!
	* \brief Corner 3 over 8 defined by a point in the 3D space
	*/
	Point m_p3;
	/*!
	* \brief Corner 4 over 8 defined by a point in the 3D space
	*/
	Point m_p4;
	/*!
	* \brief Corner 5 over 8 defined by a point in the 3D space
	*/
	Point m_p5;
	/*!
	* \brief Corner 6 over 8 defined by a point in the 3D space
	*/
	Point m_p6;
	/*!
	* \brief Corner 7 over 8 defined by a point in the 3D space
	*/
	Point m_p7;
	/*!
	* \brief Corner 8 over 8 defined by a point in the 3D space
	*/
	Point m_p8;
public:
	/*!
	* \brief Default constructor. Completly unnecessary, because this constructor define a cube
	* with all the corners (0 0 0)
	*/
	Cube();
	/*!
	* \brief Constructor of the cube
	* \param pt1 corner 1 over 8
	* \param pt2 corner 2 over 8
	* \param pt3 corner 3 over 8
	* \param pt4 corner 4 over 8
	* \param pt5 corner 5 over 8
	* \param pt6 corner 6 over 8
	* \param pt7 corner 7 over 8
	* \param pt8 corner 8 over 8
	*/
	Cube(Point, Point, Point, Point, Point, Point, Point, Point);
	/*!
	* \brief Allow the user to change the caracteristics of a cube object
	* \param pt1 corner 1 over 8
	* \param pt2 corner 2 over 8
	* \param pt3 corner 3 over 8
	* \param pt4 corner 4 over 8
	* \param pt5 corner 5 over 8
	* \param pt6 corner 6 over 8
	* \param pt7 corner 7 over 8
	* \param pt8 corner 8 over 8
	*/
	void setCube(Point, Point, Point, Point, Point, Point, Point, Point);
	void printCube();
};

#endif
