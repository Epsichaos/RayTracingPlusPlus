#include "material.h"


void Material::setRefraction(double refraction) {
    m_refraction = refraction;
}
void Material::setReflexion(double reflexion) {
    m_reflexion = reflexion;
}
bool Material::hasRefraction() {
    if(m_refraction==0) {
        return false;
    }
    else {
        return true;
    }
}
bool Material::hasReflexion() {
    if(m_reflexion==0) {
        return false;
    }
    else {
        return true;
    }
}
double Material::getRefraction() {
    return m_refraction;
}
double Material::getReflexion() {
    return m_reflexion;
}
void Material::setColorMat(Color color_mat) {
    m_color = color_mat;
}
double Material::getDiffuseFactor()
{
	return m_diffuse_factor;
}
void Material::setDiffuseFactor(double df)
{
	m_diffuse_factor = df;
}
Color Material::getColor()
{
	return m_color;
}
