#ifndef COLOR_H
#define COLOR_H

/*!
* \file color.h
* \brief File which contains the class Color and all the variables and functions associated
*/

/*!
* \class Color
* \brief Define what a color is. A color will be considered with its RGB code
*/
 class Color
 {
 protected:
     /*!
     * \brief Variable which contains the R-value of the color
     */
 	double m_R;
     /*!
     * \brief Variable which contains the G-value of the color
     */
 	double m_V;
     /*!
     * \brief Variable which contains the B-value of the color
     */
 	double m_B;
 public:
     /*!
     * \brief Default constructor. Initialize a color with (0 0 0)
     */
     Color();
     /*!
     * \brief Constructor of the color
     * \param R the R-value of the color
     * \param G the G-value of the color
     * \param B the B-value of the color
     */
     Color(double, double, double);
     /*!
     * \brief Allow the user to change the caracteristics of the color
     * \param R the R-value of the color
     * \param G the G-value of the color
     * \param B the B-value of the color
     */
     void setColor(double, double, double);
     /*!
     * \fn getRed()
     * \brief Fonction to get the R-value of the color
     * \return The R-Value
     */
     double getRed();
     /*!
     * \fn getGreen()
     * \brief Fonction to get the G-value of the color
     * \return The G-Value
     */
     double getGreen();
     /*!
     * \fn getBlue()
     * \brief Fonction to get the B-value of the color
     * \return The B-Value
     */
     double getBlue();
 };

 #endif
