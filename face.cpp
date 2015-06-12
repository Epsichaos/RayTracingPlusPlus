#include "face.h"
#include "operators.h"
Face::Face()
{
	Point null(0,0,0);
	m_p1 = null;
	m_p2 = null;
	m_p3 = null;
}
Face::Face(Point a, Point b, Point c)
{
	m_p1 = a;
	m_p2 = b;
	m_p3 = c;
}
Face::Face(Point a, Point b, Point c, Material mat)
{
	m_p1 = a;
	m_p2 = b;
	m_p3 = c;
}
Point Face::p1()
{
	return m_p1;
}
Point Face::p2()
{
	return m_p2;
}
Point Face::p3()
{
	return m_p3;
}
Vector Face::v1()
{
	return m_p2-m_p1;
}
Vector Face::v2()
{
	return m_p3-m_p1;
}
void Face::setFace(Point a, Point b, Point c)
{
	m_p1 = a;
	m_p2 = b;
	m_p3 = c;
}
Color Face::getColor(){
	return m_m1.getColor();
}
double Face::getDiffuseFactor()
{
    return m_m1.getDiffuseFactor();
}
void Face::setColor(Color c)
{
	m_m1.setColorMat(c);
}