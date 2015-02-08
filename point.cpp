#include <iostream>
#include "point.h"

using namespace std;

Point::Point() {
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

Point::Point(double x, double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

void Point::setPoint(double x,double y, double z) {
    m_x = x;
    m_y = y;
    m_z = z;
}

void Point::printPoint() {
    cout << "("<< m_x << "," << m_y << "," << m_z << ")" << endl;
}
