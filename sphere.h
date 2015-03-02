#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "point.h"
#include "vector.h"

/*!
* \file sphere.h
* \brief File which contains the class Sphere and all the variables and functions associated
*/

/*!
* \class Sphere
* \brief File which contains the class Sphere and all the variables and functions associated
*/
class Sphere : public Object
{
protected:
	/*!
	* \brief Center of the sphere
	*/
	Point m_center;
	/*!
	* \brief Radius of the sphere
	*/
	double m_radius;
public:
	/*!
	* \fn  Sphere()
	* \brief Defaut constructor of a sphere object
	*/
	Sphere();
	/*!
	* \fn Sphere(Point pt, double radius)
	* \brief Constructor of a sphere object
	* \param pt the center of the sphere
	* \param radius the radius of the sphere
	*/
	Sphere(Point, double);
	/*!
	* \fn double getRadius()
	* \brief Accessor to the radius of a sphere
	* \return The Radius of the sphere
	*/
	double getRadius();
	/*!
	* \fn double getCenter()
	* \brief Accessor to the center of a sphere
	* \return The center of the sphere
	*/
	Point getCenter();
	/*!
	* \fn setCenter(Point pt)
	* \brief Define the new center of the sphere
	* \param pt the new center of the sphere
	*/
	void setCenter(Point);
	/*!
	* \fn setRadius(double radius)
	* \brief Define the new radius of the sphere
	* \param radius the new radius
	*/
	void setRadius(double);
	void printSphere();
	Vector computeNormale(Point);
};

#endif
