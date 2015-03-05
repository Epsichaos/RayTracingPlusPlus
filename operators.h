#ifndef OPERATORS_H
#define OPERATORS_H


#include "vector.h"
#include "point.h"
#include "color.h"


Vector operator+(Vector const& a, Vector const& b);
Color operator+(Color const& a, Color const& b);
Point operator+(Point const& a, Vector const& b);
Point operator+(Vector const& a, Point const& b);
Point operator-(Point const& a, Vector const& b);
Vector operator-(Point const& a, Point const& b);
double operator*(Vector const& a, Vector const& b);
Vector operator*(Vector const& a, double const& b);
Vector operator*(double const& b, Vector const& a);
Color operator*(Color const& a, Color const& b);
Color operator*(Color const& a, double const& b);
Color operator*(double const& a, Color const& b);
#endif