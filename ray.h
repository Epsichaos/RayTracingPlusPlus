#ifndef RAY_H
#define RAY_H

#include "vector.h"
#include "point.h"

/*!
* \file ray.h
* \brief File which contains the class Ray and all the variables and functions associated
*/

/*!
* \class Ray
* \brief Contains the definition of a Ray
*/
class Ray {
public:
	/*!
	* \fn Ray()
	* \brief Default constructor of a Ray
	*/
	Ray();
	/*!
	* \fn Ray(point const pt, Vector const vect)
	* \brief Constructor of the vector
	* \param pt origin of the ray
	* \param vect vector direction of the ray
	*/
	Ray(Point const A, Vector const B);
	/*!
	* \fn getDirection()
	* \brief Accessor to the direction of the ray
	* \return The direction of the ray
	*/
	Vector getDirection();
	/*!
	* \fn getStart()
	* \brief Accessor to the origin of the ray
	* \return The point origin of the ray
	*/
	Point getStart();
	/*!
	* \fn setDirection(vector const vect)
	* \brief Set the new direction of the ray
	* \param vect the new vector direction
	*/
	void setDirection(Vector const A);
	/*!
	* \fn setStart(Point const pt)
	* \brief Set the new start point of the ray
	* \param pt the new start point
	*/
	void setStart(Point const A);
protected:
	/*!
	* \brief Origin of the ray
	*/
	Point m_start;
	/*!
	* \brief Vector direction of the ray
	*/
	Vector m_direction;
};

#endif
