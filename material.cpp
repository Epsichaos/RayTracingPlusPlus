#include "material.h"

void Material::setColorMat(Color color_mat) {
    m_color = color_mat;
}
double Material::getDiffuseFactor()
{
	return m_diffuse_factor;
}

Color Material::getColor()
{
	return m_color;
}