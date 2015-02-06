#ifndef RAY_H
#define RAY_H

class ray
{
	vector getDirection();
	Point getStart();
protected:
	Point m_start;
	Vector m_direction;
};

#endif
