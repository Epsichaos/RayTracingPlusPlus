#ifndef LIGHT_H
#define LIGHT_H

#include "object.h"
#include "point.h"

class Light : public Object
{
public:
	void setSource(Point);
	void setIntensity(float);
	void printLight();
protected:
	Point m_source;
	double m_intensity;
};

#endif
