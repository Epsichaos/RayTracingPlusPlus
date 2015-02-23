#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

/*!
* \file material.h
* \brief File which contains the class Material and all the variables and functions associated
*/

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
