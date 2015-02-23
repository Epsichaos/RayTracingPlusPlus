#ifndef POINT_H
#define POINT_H

/*!
* \file point.h
* \brief File which contains the class Point and all the variables and functions associated
*/

class Point
{
	protected:
		double m_x;
		double m_y;
		double m_z;
	public:
		Point();
		Point(double, double, double);
		double x();
		double y();
		double z();
		void setPoint(double, double, double);
		void printPoint();
};

#endif
