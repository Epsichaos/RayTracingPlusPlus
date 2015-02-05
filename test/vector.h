#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
	Vector();
	Vector(double, double, double);
	double getX();
	double getY();
	double getZ();
	void setVector(double, double, double);
protected:
	double m_x;
	double m_y;
	double m_z;
};

#endif
