#include <iostream>
#include "sphere.h"
#include "point.h"
#include "fonctions.h"
#include "operators.h"
using namespace std;

Sphere::Sphere() {
    m_center = Point();
    m_radius = 0;
}
Sphere::Sphere(Point center, double radius) {
    m_center = center;
    m_radius = radius;
}
void Sphere::setCenter(Point center) {
    m_center = center;
}
void Sphere::setRadius(double radius) {
    m_radius = radius;
}
double Sphere::getRadius() {
    return m_radius;
}
Point Sphere::getCenter() {
    return m_center;
}
void Sphere::printSphere() {
    cout << "La sphere a pour rayon " << m_radius << " et pour centre ";
    m_center.printPoint();
}
Vector Sphere::computeNormale(Point a)
{
    Vector b =(a-m_center);
    b.normalize();
return b;
}
