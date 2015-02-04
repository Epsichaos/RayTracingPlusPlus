#include <iostream>
#include "sphere.h"
#include "point.h"

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

void Sphere::printSphere() {
    cout << "La sphere : " << m_radius << endl;
    m_center.printPoint();
}
