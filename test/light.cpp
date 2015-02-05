#include <iostream>
#include "light.h"
#include "point.h"
using namespace std;

void Light::setCenter(Point center) {
    m_center = center;
}

void Light::setIntensity(float intensity) {
    m_intensity = intensity;
}

void Light::printLight() {
    cout << "Light, de centre";
    m_center.printPoint();
    cout << "et d'intensité " << m_intensity << endl;
}
