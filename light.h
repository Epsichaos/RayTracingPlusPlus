#ifndef LIGHT_H
#define LIGHT_H

#include "object.h"
#include "point.h"

/*!
* \file light.h
* \brief File which contains the class Light and all the variables and functions associated
*/

/*!
* \class Light
* \brief Contains the description of a Light object
* This class, derivated from the class Object define what a light is.
*/
class Light : public Object
{
public:
	/*!
	* \fn setSource(Point pt)
	* \brief Set the new source point of the light
	* \param pt the new source of the light
	*/
	void setSource(Point);
	/*!
	* \fn setIntensity(double intens)
	* \brief Set the new intensity of the light
	* \param intens the new intensity
	*/
	void setIntensity(double);
	void printLight();
protected:
	/*!
	* \brief Point source of the light
	*/
	Point m_source;
	/*!
	* \brief Intensity of the light issued from the point defined above
	*/
	double m_intensity;
};

#endif
