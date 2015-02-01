#ifndef POINT_H
#define POINT_H

class Point
{
	protected:
		double m_x;
		double m_y;
		double m_z;
	public:
		Point();
		Point(double, double, double);
		void setPoint(double, double, double);
		void printPoint();
};

#endif
