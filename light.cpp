#include <iostream>
#include "light.h"
#include "point.h"
using namespace std;

void Light::setSource(Point source) {
    m_source = source;
}

void Light::setIntensity(double intensity) {
    m_intensity = intensity;
}

void Light::printLight() {
    cout << "Light, de centre";
    m_source.printPoint();
    cout << "et d'intensité " << m_intensity << endl;
}
