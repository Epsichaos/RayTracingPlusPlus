#include "mesh.h"

Mesh::Mesh()
{

}
unsigned int Mesh::getNumberOfFace()
{
	return m_number_of_faces;
}
void Mesh::defineFaces(Face *tab, unsigned int nf)
{
	unsigned int i;
	m_number_of_faces = nf;
	m_faces = new Face[nf];
	for(i=0;i<nf;i++)
	{
		m_faces[i]=tab[i];
	}
}
void Mesh::getFaceArray(Face* faces)
{
	unsigned int i;
	for(i=0;i<m_number_of_faces;i++)
	{
		faces[i]=m_faces[i];
	}
}
void Mesh::getNormalesArray(Vector* input)
{
	unsigned int i;
	for(i=0;i<m_number_of_faces;i++)
	{
		input[i]=m_normales[i];
	}
}
void Mesh::defineNormales(Vector *tab, unsigned int nn){
		unsigned int i;
	m_normales = new Vector[nn];
	for(i=0;i<nn;i++)
	{
		m_normales[i]=tab[i];
	}
}
Mesh::~Mesh()
{
delete[] m_faces;
delete[] m_normales;

}