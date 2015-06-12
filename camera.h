#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "object.h"
#include "point.h"
#include <string>

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
	Camera(Point, Vector, int, int, double, std::string);
	Camera(Point, Vector, int, int, double,Vector,Vector);
	/*!
	* \brief Allow the user to set or change the position of the camera
	* \param pt a point which is the new position, the new center of the camera
	*/
	Camera();
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
	/*! \brief Allow the user to set or change the set of the camera
	* \param String, which is true or false
	*/
	void setState(std::string);
	/*! \brief Accessor to the angle of the camera
	*/
	double getAngle();
	/*! \brief Accessor to the position of the camera
	*/
	Point getPosition();
	/*! \brief Accessor to the direction of the camera
	*/
	Vector getDirection();
	/*! \brief Accessor to the X-orientation of the camera
	*/
	Vector getOrientationX();
	/*! \brief Accessor to the Y-orientation of the camera
	*/
	Vector getOrientationY();
	/*! \briel Set the X-orinetation of the camera
	* \param Vector the X-orientation 
	*/
	void setOrientationX(Vector);
	/*! \briel Set the X-orinetation of the camera
	* \param Vector the Y-orientation 
	*/
	void setOrientationY(Vector);
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
	/*!
	* \brief It's the state of the camera, which can be `true` or `false`. We wanted to let the possibility
	*for the user to declare more than one camera per scene, but only one shuld be active at the same time. The 
	*others must be disabled.
	*/
	int m_state;
	/*!
	* \brief X-Orientation of the camera (X-axis)
	*/
	Vector m_orientationX;
	/*!
	* \brief Y-Orientation of the camera (Y-axis)
	*/
	Vector m_orientationY;
};

#endif
