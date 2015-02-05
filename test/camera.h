#ifndef CAMERA_H
#define CAMERA_H

class Camera : Object
{
public:
protected:
	point m_position;
	vector direction;
	int m_width;
	int m_height;
	double m_angle;
};

#endif
