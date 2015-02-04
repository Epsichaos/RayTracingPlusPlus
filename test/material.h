#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

class Material
{
 protected:
 	double m_reflexion;
 	double m_refraction;
 	Color m_color;
public:
    void setColorMat(Color);
 };

#endif
