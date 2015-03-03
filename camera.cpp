#include <iostream>
#include "camera.h"
#include "vector.h"
#include "point.h"

using namespace std;

Camera::Camera(Point position, Vector direction, int width, int height, double angle, Vector orientationX, Vector orientationY) {
    m_position = position;
    m_direction = direction;
    m_width = width;
    m_height = height;
    m_angle = angle;
    m_orientationX = orientationX;
    m_orientationY = orientationY;
}
Camera::Camera()
{
	
}
void Camera::setPosition(Point position) {
    m_position = position;
}

void Camera::setDirection(Vector direction) {
    m_direction = direction;
}

void Camera::setSize(int width, int height) {
    m_width = width;
    m_height = height;
}

void Camera::setAngle(double angle) {
    m_angle = angle;
}

void Camera::setState(string str) {
    if(str=="true") {
        m_state = 1;
    }
    if(str=="false") {
        m_state = 0;
    }
}

void Camera::printCamera() {
    cout << "Camera de position";
    m_position.printPoint();
    cout << " de taille " << m_width << "x" << m_height << endl;
}
double Camera::getAngle()
{
	return m_angle;
}
Point Camera::getPosition()
{
	return m_position;
}
Vector Camera::getDirection()
{
	return m_direction;
}
Vector Camera::getOrientationX()
{
	return m_orientationX;
}
Vector Camera::getOrientationY()
{
	return m_orientationY;
}
void Camera::setOrientationX(Vector orientationX)
{
    m_orientationX = orientationX;
}
void Camera::setOrientationY(Vector orientationY)
{
    m_orientationY = orientationY;
}