#ifndef VECTOR_H
#define VECTOR_H

/*!
* \file vector.h
* \brief File which contains the class Vector and all the variables and functions associated
*/

class Vector {
public:
	Vector();
	Vector(double, double, double);
	double x();
	double y();
	double z();
	void setVector(double, double, double);
protected:
	double m_x;
	double m_y;
	double m_z;
};

#endif
