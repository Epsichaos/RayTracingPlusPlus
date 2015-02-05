#ifndef LIGHT_H
#define LIGHT_H

#include "point.h"
#include "object.h"

class Light : public Object {
public:
    void setCenter(Point);
    void setIntensity(float);
    void printLight();
protected:
    Point m_center;
    float m_intensity;
};

#endif
