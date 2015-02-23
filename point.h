#ifndef POINT_H
#define POINT_H

/*!
* \file point.h
* \brief File which contains the class Point and all the variables and functions associated
*/

class Point
{
	protected:
		/*!
		* \brief first component over 3 in the 3D space
		*/
		double m_x;
		/*!
		* \brief second component over 3 in the 3D space
		*/
		double m_y;
		/*!
		* \brief third component over 3 in the 3D space
		*/
		double m_z;
	public:
		/*!
		* \brief Default constructor. Initialize a point with (0 0 0)
		*/
		Point();
		/*!
		* \brief Constructor
		* \param x define the first component
		* \param y define the second component
		* \param z define the third component
		*/
		Point(double, double, double);
		/*!
		* \brief Accessor to the first component
		* \return x the first component of the point
		*/
		double x();
		/*!
		* \brief Accessor to the second component
		* \return y the second component of the point
		*/
		double y();
		/*!
		* \brief Accessor to the third component
		* \return z the third component of the point
		*/
		double z();
		/*!
		* \brief Allow the user to change the components of a point
		*/
		void setPoint(double, double, double);
		void printPoint();
};

#endif
