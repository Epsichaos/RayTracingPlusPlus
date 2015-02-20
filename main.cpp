#include <iostream>
#include "point.h"
#include "cube.h"
#include "sphere.h"
#include "scene.h"

using namespace std;

int main() {
/*
    Point pt1(1,2,3);
    pt1.setPoint(3,4,5);
    Cube cu1(pt1, pt1, pt1, pt1, pt1, pt1, pt1, pt1);
    cu1.printCube();
    Sphere spr(pt1, 3);
    Scene scene;
*/
    Scene scene("input");
    //scene.loadScene("input");
    cout << scene.getNumberOfObjects() << endl;
    scene.debugTest();
}
