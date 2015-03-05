#include "mesh.h"

Mesh::Mesh()
{

}
void Mesh::setNumberofFace(unsigned int nf)
{
	m_number_of_faces = nf;
}
unsigned int Mesh::getNumberOfFace()
{
	Point n(0,0,0);
	return n;
	//return m_number_of_faces;
}
void Mesh::defineFaces(Face *tab, unsigned int nf)
{
	unsigned int i;
	m_faces = new Face[nf];
	for(i=0;i<nf;i++)
	{
		m_faces[i]=tab[i];
	}
}
Face* Mesh::getFaceArray()
{
	return m_faces;
}