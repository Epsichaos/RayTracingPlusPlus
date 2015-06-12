#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "camera.h"
#include "sphere.h"
#include "mesh.h"
#include "face.h"



/*!
* \file scene.h
* \brief File which contains the class Scene and all the variables and functions associated
*/

/*! \class Scene
* \brief Contains the main scene description and all the objects included in.
* This class will be used to store all the objects present in the input file.
*/
class Scene
{
public:
	/*! \brief Constructor of the Scene class.
	* \param *path* of the input file
	*/
	Scene(const std::string,double);
	/*! \brief Accessor to the objects
	* \return The number of all the objects
	*/
	int getNumberOfObjects();
		/*! \brief Accessor to the active camera
	* \return A handler to the active Camera
	*/
	Camera getActiveCamera();
	/*! \brief Accessor to one specific type of object
	* \param str a string which contains the name of the class. **str** can be *light*, *camera* or *sphere*
	* \return The number of the objects of one specific class
	*/
	int getNumberOfObjects(std::string);
	/*! \brief Accessor to the camera. Fill a tab with all the camera objects
	*/
	void getCameras(Camera *tab);
	/*! \brief Accessor to the lights. Fill a tab with all the light objects
	*/
	void getLights(Light *tab);
	/*! \brief Accessor to the spheres. Fill a tab with all the sphere objects
	*/
	void getSpheres(Sphere *tab);
	/*! \brief Accessor to the number of mesh faces.
	* \return the number of mesh faces
	*/
	unsigned int getNumberOfMeshFaces();
	/*! \brief Accessor to the faces of a mesh.
	*/
	void getFaces(Face*);
	/*! \brief Accessor to the normales to the faces of a mesh
	*/
	void getNormales(Vector*);
	void getMesh(Mesh*);
	~Scene();
protected:
	/*!
	* \brief Number of all the objects
	*/
	int m_objectNumber;
	
	Mesh m_mesh;
	/*!
	* \brief Number of all the sphere objects
	*/
	int m_sphereNumber;
	/*!
	* \brief Number of all the camera objects
	*/
	int m_cameraNumber;
	/*!
	* \brief Number of all the ligth objects
	*/
	int m_lightNumber;
	//Object* m_arrayOfObjects;
	/*!
	* \brief Array which contains all the sphere objects
	*/
	Sphere *m_arrayOfSphere;
	/*!
	* \brief Array which contains all the camera objects
	*/
	Camera *m_arrayOfCamera;
	/*!
	* \brief Array which contains all the light objects
	*/
	Light *m_arrayOfLight;
	/*!
	* \brief The id of the active camera in the array of camera in case where there are multiple cameras ( default : 0)
	*/
	int m_idActiveCamera;
};

#endif
