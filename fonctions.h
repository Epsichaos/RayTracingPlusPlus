#include <cmath>
#include <cstring>
#include <iostream>
#include "ray.h"
#include "scene.h"
#include "object.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "camera.h"
#include "cube.h"
#include "light.h"
#include "sphere.h"
#ifndef FONCTIONS_H
#define FONCTIONS_H

void render(Scene & Mainscene, Color* image, int width, int height);
Color lancer_rayon(Ray rayon, Scene scene, int current_depth);
Point computeIntersection(Ray, Sphere);
int findClosest(Ray r, Point*, int);
void fill_tabX_tabY(Point **tabCenters,Point camerapos,Vector cameradir, Vector orientationX,Vector orientationY, int width, int height);
double computeShadow(Point, Sphere*,int , Light,int);
void tabToBMP(Color *image, int w, int h, std::string path);
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
