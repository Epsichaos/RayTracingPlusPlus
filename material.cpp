#include "material.h"

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