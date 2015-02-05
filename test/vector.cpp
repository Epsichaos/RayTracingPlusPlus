#include "vector.h"

using namespace std;

Vector::Vector() {
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

Vector::Vector(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

double Vector::getX() {
    return m_x;
}

double Vector::getY() {
    return m_y;
}
double Vector::getZ() {
    return m_z;
}

void Vector::setVector(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}
