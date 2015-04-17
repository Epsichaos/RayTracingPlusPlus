#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

/*!
* \file material.h
* \brief File which contains the class Material and all the variables and functions associated
*/

/*!
* \class Material
* \brief Class which define the material of all the objects, and the properties
* associated (reflexion, refraction, color)
*/
class Material
{
 protected:
     /*!
     * \brief Reflexion coefficient
     */
 	double m_reflexion;
     /*!
     * \brief Refraction coefficient
     */
 	double m_refraction;
     /*!
     * \brief Color of the material
     */
 	Color m_color;
 	double m_diffuse_factor;
 	double m_ambient_factor;
public:
    /*!
    * \fn setColorMat(Color c)
    * \brief Set c as the new color of the material
    * \param c the new color
    */
    double getDiffuseFactor();
    void setColorMat(Color);
    void setDiffuseFactor(double);
    void setRefraction(double);
    void setReflexion(double);
    int hasRefraction();
    int hasReflexion();
    Color getColor();
    double getReflexion();
    double getRefraction();
 };

#endif
