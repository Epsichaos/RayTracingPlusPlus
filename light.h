#ifndef LIGHT_H
#define LIGHT_H

class Light : Object
{
protected:
	point m_source;
	color m_color;
	double m_intensity;
};

#endif
