#include <iostream>
#include "cube.h"
#include "point.h"

using namespace std;

Cube::Cube() {
    Point m_p1, m_p2, m_p3,m_p4,m_p5,m_p6,m_p7,m_p8;
}

Cube::Cube(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8) {
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
    m_p4 = p4;
    m_p5 = p5;
    m_p6 = p6;
    m_p7 = p7;
    m_p8 = p8;
}
void Cube::setCube(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8) {
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
    m_p4 = p4;
    m_p5 = p5;
    m_p6 = p6;
    m_p7 = p7;
    m_p8 = p8;
}
void Cube::printCube() {
    m_p1.printPoint();
    m_p2.printPoint();
    m_p3.printPoint();
    m_p4.printPoint();
    m_p5.printPoint();
    m_p6.printPoint();
    m_p7.printPoint();
    m_p8.printPoint();
}
