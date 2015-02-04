#include <iostream>
#include "cube.h"
#include "point.h"

using namespace std;

Cube::Cube() {
    m_p1 = Point::Point();
    m_p2 = Point::Point();
    m_p3 = Point::Point();
    m_p4 = Point::Point();
    m_p5 = Point::Point();
    m_p6 = Point::Point();
    m_p7 = Point::Point();
    m_p8 = Point::Point();
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
}
