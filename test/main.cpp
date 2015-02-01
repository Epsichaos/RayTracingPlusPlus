#include <iostream>
#include "point.h"
#include "cube.h"
#include "sphere.h"

int main() {
    Point pt1(1,2,3);
    pt1.printPoint();
    pt1.setPoint(3,4,5);
    pt1.printPoint();
    Cube cu1(pt1, pt1, pt1, pt1, pt1, pt1, pt1, pt1);
    cu1.printCube();
    Sphere spr(pt1, 3);
}
