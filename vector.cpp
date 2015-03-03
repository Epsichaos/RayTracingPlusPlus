#include "vector.h"
#include "cmath"
#include "fonctions.h"
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
double Vector::getNorm()
{
    return  sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
}
/*
Vector Vector::getOrthonormalDVector(Vector input)
{
    Vector temp(m_x,m_y,m_z);
    Vector output;
    if(input*temp == input.getNorm()*temp.getNorm())
        output.setVector(0,0,0);
    else
    {
        output.setVector((m_z*input.y()-input.z()*m_y)/(m_y*input.x()-m_x*input.y()),-(m_z*input.x()-input.z()*m_x)/(m_y*input.x()-m_x*input.y()) ,1.0);
        output.normalize();
    }
    return output;
}
*/