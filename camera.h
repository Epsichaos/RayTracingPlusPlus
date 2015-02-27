#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "object.h"
#include "point.h"

/*!
* \file camera.h
* \brief File which contains the class Camera and all the variables and functions associated
*/

/*! \class Camera
* \brief Contains the description of a Camera object
* This class, derivated from the class Object define what a camera is.
*/
class Camera : public Object {
public:
	/*!
	* \brief Constructor of the camera
	* \param pt a point which is the center of the camera
	* \param v a vector which define the direction of the camera
	* \param width an int which define the width of the camera
	* \param height an int which define the height of the camera
	* \param angle a double which set the angle of the camera
	*/
	Camera(Point, Vector, int, int, double);
	/*!
	* \brief Allow the user to set or change the position of the camera
	* \param pt a point which is the new position, the new center of the camera
	*/
	void setPosition(Point);
	/*!
	* \brief Allow the user to set or change the direction of the camera
	* \param v a vector which is the new direction of the camera
	*/
	void setDirection(Vector);
	/*!
	* \brief Allow the user to set or change the size of the camera
	* \param width an int which define the new width of the camera
	* \param height an int which define the new height of the camera
	*/
	void setSize(int, int);
	/*!
	* \brief Allow the user to set or change the angle of the camera
	* \param angle a double which is the new angle
	*/
	void setAngle(double);
	void printCamera();
	double getAngle();
	Point getPosition();
	Vector getDirection();
protected:
	/*!
	* \brief *Point* which define the center of the camera
	*/
	Point m_position;
	/*!
	* \brief *Vector* which define the direction of the camera
	*/
	Vector m_direction;
	/*!
	* \brief Width (in pixels) of the camera (à expliquer mieux)
	*/
	int m_width;
	/*!
	* \brief Height (in pixels) of the camera (à expliquer mieux)
	*/
	int m_height;
	/*!
	* \brief *Angle* of the camera
	*/
	double m_angle;
};

#endif
