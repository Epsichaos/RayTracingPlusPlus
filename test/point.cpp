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
    cout << "La 1ere composante du point "<< m_x << endl;
    cout << "La 2ème composante du point "<< m_y << endl;
    cout << "La 3ème composante du point "<< m_z << endl;
}
