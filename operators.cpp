#include "operators.h"
Vector operator+(Vector const &a, Vector const &b)
{
	Vector c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}

Color operator+(Color const& a, Color const& c)
{
	double r =a.getRed()+c.getRed() ,v = a.getGreen()+c.getGreen(),b=a.getBlue()+c.getBlue();
	Color d((r<=1?r:1.0),(v<=1?v:1.0),(b<=1?b:1.0));
	return d;
}

Point operator+(Point const& a, Vector const& b)
{
	Point c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}
Point operator-(Point const& a, Vector const& b)
{
	Point c(a.x()-b.x(), a.y()-b.y(), a.z()-b.z());
	return c;
}
Point operator+(Vector const& a, Point const& b)
{
	Point c(a.x()+b.x(), a.y()+b.y(), a.z()+b.z());
	return c;
}
Vector operator*(Vector const& a, double const& b)
{
	Vector c(a.x()*b, a.y()*b, a.z()*b);
	return c;
}
Vector operator*(double const& b, Vector const& a)
{
	Vector c(a.x()*b, a.y()*b, a.z()*b);
	return c;
}
double operator*(Vector const& a, Vector const& b)
{
	return (a.x()*b.x()+a.y()*b.y()+a.z()*b.z());
}

Color operator*(Color const& a, Color const& b)
{
	Color c(a.getRed()*b.getRed(),a.getGreen()*b.getGreen(),a.getBlue()*b.getBlue());
	return c;
}
Color operator*(double const& a, Color const& b)
{
	Color c(a*b.getRed(),a*b.getGreen(),a*b.getBlue());
	return c;
}
Color operator*(Color const& a, double const& b)
{
	Color c(a.getRed()*b,a.getGreen()*b,a.getBlue()*b);
	return c;
}

Vector operator-(Point const& a, Point const& b)
{
	Vector c(a.x()-b.x(),a.y()-b.y(),a.z()-b.z());
	return c;
}