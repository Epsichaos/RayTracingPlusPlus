#ifndef SCENE_H
#define SCENE_H

#include "light.h"
#include "camera.h"
#include "cube.h"
#include "sphere.h"

class Scene
{
public:
	Scene(const std::string path);
	int getNumberOfObjects();
	int getNumberOfObjects(std::string);
	// fonction de test pour débugger
	void debugTest();
	//void getObjects(Object* input_array);
	//void getObjects(Object* input_array, enum m_type type);
protected:
	int m_objectNumber;
	int m_sphereNumber;
	int m_cameraNumber;
	int m_cubeNumber;
	int m_lightNumber;
	//Object* m_arrayOfObjects;
	Sphere *m_arrayOfSphere;
	Cube *m_arrayOfCube;
	Camera *m_arrayOfCamera;
	Light *m_arrayOfLight;
};

#endif
