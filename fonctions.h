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
#include "light.h"
#include "sphere.h"
#include "mesh.h"
#include "face.h"
#ifndef FONCTIONS_H
#define FONCTIONS_H

/*!
* \file fonctions.h
* \brief File which contains the main functions which are the core of the raytracer, such as the rendering
* fonction, or the calculus of the shadows and the shading. 
*/

/*! \brief Rendering function which fill the image
* \param Scene the scene
* \param Image the image to fill
* \param Width the width of the image
* \param Height the height of the image
*/
void render(Scene & Mainscene, Color* image, int width, int height);

/*! \brief Calculus of the fresnel factor
* \param Normal_vector the normal vector to the current object/point
* \param Incident_vector the incident vector to the current object
* \param n1 the refractive indice of the first place (incident vector)
* \param n2 the refractive indice of the second place (refracted vector)
* \return fresnel_factor the coefficient of fresnel
*/
double fresnel(const Vector& v_normal, const Vector& v_incident,double n1, double n2);

/*! \brief Function which launch the rays into the scene
* \param Ray the incident ray to launch
* \param Scene the scene in which we launch the ray
* \param Depth the current depth of calculus (for refraction/reflexion)
* \param Faces array of all the faces
* \param Normales the array of the normales at every faces
* \param Spheres array of all the spheres
* \param Lights array of all the lights
* \param Camera array of all the cameras
* \param Sphere_number number of all the spheres
* \param Camera_number number of all the cameras
* \param Light_number number of all the lights
* \param Intersect_mesh number of all the intersection with the mesh
* \param Refraction the refraction factor of the current place
* \param Inside int which say if we are inside an object or not
* \param Mesh the mesh object
* \return Color The color of the current pixel
*/
Color lancer_rayon(Ray rayon, Scene &scene, int current_depth, Face *faces,Vector *normales, Sphere *spheres, Light *lights,Camera *cameras,int number_of_spheres,int number_of_cameras,int number_of_lights,unsigned	int number_of_intersections_mesh, double  indice_refract, int inside, Mesh & mesh);
/*! \brief Function which is launched by each thread and that calls lancer_rayon
* \param arg the args for lancer_rayon
*/
void* lancer_rayon_thread(void* arg);
/*! \brief Function which compute the intersection point between a ray and a sphere. 
* \param Ray the incident ray which is launched
* \param Sphere the object sphere intersected (or not) by the ray
* \return Point the intersection between the ray and the sphere, or if this point does not exist, a specific
* point which means *there is no intersections here* (a point at the infinity)
*/

Point computeIntersection(Ray, Sphere);

/*! \brief Function which compute the intersection point between a ray and a face. This function overload
* the function above.
* \param Ray the incident ray which is launched
* \param Face the object face intersected (or not) by the ray
* \return Point the intersection between the ray and the face, or if this point does not exist, a specific
* point which means *there is no intersections here* (a point at the infinity)
*/
Point computeIntersection(Ray ,Face, Vector);

/*! \brief Function which find the closest point in a list of different intersection points
* \param Ray the incident ray which is launched
* \param Point* the array of all the intersected points
* \param Size the size of the array Point*
* \return Position an int which is the position of the closest point intersected by the ray
*/
int findClosest(Ray r, Point*, int);

/*! \brief Function which fill an array, depending of the camera. This array is the image, viewed by the 
*camera. This array contains the center of the pixel in the real 3D-space
* \param tabCenter the array of the center of the points
* \param CameraPos the position of the camera
* \param CameraDir the vector direction of the camera
* \param OrX the axis X of the camera
* \param OrY the axis Y of the camera
* \param Width the width of the image
* \param Height the height of the image
*/
void fill_tabX_tabY(Point **tabCenters,Point camerapos,Vector cameradir, Vector orientationX,Vector orientationY, int width, int height);

/*! \brief Function which find the closest point in a list of different intersection points
* \param Ray the incident ray which is launched
* \param Point* the array of all the intersected points
* \param Size the size of the array Point*
* \return Position an int which is the position of the closest point intersected by the ray
*/
double computeShadow(Point, Sphere*,int , Light,int);

/*! \brief Function which compute the shadow factor on a Face
* \param Point where we need to compute the current shadow factor
* \param Face the array of all the faces
* \param Normales the array of the normale related to the faces
* \param Light the light which is actually used to compute the shadow factor
* \param id the id of the current face, to avoid computing a shadow on a face considering itself
*/
double computeShadow(Point, Face*,Vector* ,unsigned int , Light,int);

/*! \brief Function which saves the image into a .bmp file
* \param Image the image
* \param W the width of the image to save
* \param H the height of the image to save
* \param path the path and name of the image to save
*/
void tabToBMP(Color *image, int w, int h, std::string path);

#endif
