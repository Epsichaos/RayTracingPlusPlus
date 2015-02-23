#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "camera.h"
#include "cube.h"
#include "sphere.h"

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
	Scene(const std::string path);
	/*! \brief Accessor to the objects
	* \return The number of all the objects
	*/
	int getNumberOfObjects();
	/*! \brief Accessor to one specific type of object
	* \param str a string which contains the name of the class. **str** can be *light*, *camera*, *cube* or *sphere*
	* \return The number of the objects of one specific class
	*/
	int getNumberOfObjects(std::string);
	// fonction de test pour débugger
	void debugTest();
	//void getObjects(Object* input_array);
	//void getObjects(Object* input_array, enum m_type type);
protected:
	/*!
	* \brief Number of all the objects
	*/
	int m_objectNumber;
	/*!
	* \brief Number of all the sphere objects
	*/
	int m_sphereNumber;
	/*!
	* \brief Number of all the camera objects
	*/
	int m_cameraNumber;
	/*!
	* \brief Number of all the cube objects
	*/
	int m_cubeNumber;
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
	* \brief Array which contains all the cube objects
	*/
	Cube *m_arrayOfCube;
	/*!
	* \brief Array which contains all the camera objects
	*/
	Camera *m_arrayOfCamera;
	/*!
	* \brief Array which contains all the light objects
	*/
	Light *m_arrayOfLight;
};

#endif
