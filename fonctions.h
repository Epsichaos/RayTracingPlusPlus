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
#include "mesh.h"
#include "face.h"
#ifndef FONCTIONS_H
#define FONCTIONS_H

void render(Scene & Mainscene, Color* image, int width, int height);
Color lancer_rayon(Ray rayon, Scene scene, int current_depth);
Point computeIntersection(Ray, Sphere);
int findClosest(Ray r, Point*, int);
void fill_tabX_tabY(Point **tabCenters,Point camerapos,Vector cameradir, Vector orientationX,Vector orientationY, int width, int height);
double computeShadow(Point, Sphere*,int , Light,int);
void tabToBMP(Color *image, int w, int h, std::string path);

#endif
