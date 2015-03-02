#include "vector.h"
#include "cmath"
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

double Vector::x() const {
    return m_x;
}

double Vector::y() const{
    return m_y;
}
double Vector::z() const{
    return m_z;
}

void Vector::setVector(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}
void Vector::normalize()
{
    double norm = sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
    m_x /=norm;
    m_y /=norm;
    m_z /=norm;
}
