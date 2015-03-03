#ifndef VECTOR_H
#define VECTOR_H

/*!
* \file vector.h
* \brief File which contains the class Vector and all the variables and functions associated
*/

/*!
* \class Vector
* \brief This class define a vector in the 3D space
*/
class Vector {
public:
	/*!
	* \fn Vector()
	* \brief Default constructor of a vector object
	* Set 0 to all the components
	*/
	Vector();
	/*!
	* \fn Vector(double x, double y, double z)
	* \brief Constructor of a vector object. Set (x, y, z) as the components
	* \param x the first component
	* \param y the second component
	* \param z the last component
	*/
	Vector(double, double, double);
	/*!
	* \fn double x()
	* \brief Accessor to the first component
	* \return x the first component
	*/
	double x() const;
	/*!
	* \fn double y()
	* \brief Accessor to the second component
	* \return y the second component
	*/
	double y() const;
	/*!
	* \fn double z()
	* \brief Accessor to the third component
	* \return z the third component
	*/
	double z() const;
	/*!
	* \fn setVector(double x, double y, double z)
	* \brief Change the components of one vector object
	* \param x the new first component
	* \param y the new second component
	* \param z the new third component
	*/
	void setVector(double, double, double);
	void normalize();
	Vector getOrthonormalDVector(Vector);
	double getNorm();
protected:
	/*!
	* \brief 1 component over 3 of the vector
	*/
	double m_x;
	/*!
	* \brief 2 component over 3 of the vector
	*/
	double m_y;
	/*!
	* \brief 3 component over 3 of the vector
	*/
	double m_z;
};

#endif
